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

int cmp_point_x(const void *p1, const void *p2)
{
    double *pa = (double *)p1;
    double *pb = (double *)p2;
    return pa[0] - pb[0];
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
	
	ui->pointTable->horizontalHeader()->setVisible(true);
	
	ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
    ui->plot->xAxis->setRange(-1, 1);
    ui->plot->yAxis->setRange(-1, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
	clear_matrix(plist, n);
}

void MainWindow::on_loadButton_released()
{
	QString fstr = ui->fileEdit->text();
	std::string filestr = fstr.toStdString();
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
	double *sle_col = (double *) calloc(n + 1, sizeof(double));
	if (!sle_col)
	{
		free_matrix(sle, n + 1);
        QMessageBox::critical(this, "Ошибка", "Ошибка выделения памяти!");
        return;
    }
    sle = sle_matrix(plist, plist_size, n, sle_col);
    if (!sle || !sle_col)
    {
        QMessageBox::critical(this, "Ошибка", "Ошибка выделения памяти!");
        return;
    }
	
    double **matrix = solve(sle, n);
    double *cres = multiply(matrix, sle_col, n);
	
	print_matrix(matrix, n + 1, n + 1);
	
	for (int i = 0; i < n + 1; i++)
		printf("%lf ", cres[i]);
	printf("\n");
	
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
