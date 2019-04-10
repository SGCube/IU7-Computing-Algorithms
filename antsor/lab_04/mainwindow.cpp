#include <QTableWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <cstdio>
#include <cmath>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "error.h"
#include "func.h"
#include "matrix.h"
#include "matrixsolve.h"
#include "plot.h"

double func(double x)
{
	return pow(x - 5, 3);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	setWindowTitle("Лабораторная работа №4");
	
	plist = NULL;
	plist_size = 0;
	n = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
	clear_matrix(plist, n);
}

void MainWindow::on_loadButton_released()
{
	QString str = QFileDialog::getOpenFileName(this, "Открыть файл",
												   QDir::currentPath(),
												   "All files (*.*)");
	if (str == nullptr)
		return;
	std::string filestr = str.toStdString();
	const char *filename = filestr.c_str();
	FILE *fin = fopen(filename, "r");
	if (!fin)
	{
		QMessageBox::critical(this, "Ошибка", "Невозможно открыть файл!");
		return;
	}
	plist = read_matrix(fin, &plist_size);
	if (!plist)
	{
		QMessageBox::critical(this, "Ошибка", "Ошибка чтения таблицы!");
		fclose(fin);
		return;
	}
	table_clear();
	data_to_table();
	fclose(fin);
}

void MainWindow::on_solveButton_released()
{
	if (plist_size < 1)
	{
		QMessageBox::critical(this, "Ошибка", "Задайте точки!");
		return;
	}
	
	bool correct = true;
	QString nstr = ui->nEdit->text();
	n = nstr.toInt(&correct);
	if (!correct || n < 0)
	{
		QMessageBox::critical(this, "Ошибка", "Некорректное значение n!");
		return;
	}
	
    double **sle = NULL;
	double *sle_col = NULL;
    sle = sle_matrix(plist, plist_size, n, &sle_col);
    if (!sle || !sle_col)
    {
        QMessageBox::critical(this, "Ошибка", "Ошибка выделения памяти!");
        return;
    }
	
    double **matrix = NULL;
    if (n < plist_size)
        matrix = solve(sle, n);
    double *cres = multiply(matrix, sle_col, n + 1);
	
    draw_plot(ui->plot, plist, plist_size, cres, n);
	
    free_matrix(sle, n + 1);
    free_matrix(matrix, n + 1);
	free(sle_col);
    free(cres);
}

void MainWindow::data_to_table()
{
	double x, y, p;
	for (int i = 0; i < plist_size; i++)
	{
		x = plist[i][0];
		y = plist[i][1];
		p = plist[i][2];
		ui->pointTable->insertRow(i);
		QTableWidgetItem *xitem = new QTableWidgetItem(QString::number(x));
		QTableWidgetItem *yitem = new QTableWidgetItem(QString::number(y));
		QTableWidgetItem *pitem = new QTableWidgetItem(QString::number(p));
		ui->pointTable->setItem(i, 0, xitem);
		ui->pointTable->setItem(i, 1, yitem);
		ui->pointTable->setItem(i, 2, pitem);
	}
}

void MainWindow::table_clear()
{
	while (ui->pointTable->rowCount() > 0)
		ui->pointTable->removeRow(0);
}
