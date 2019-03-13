#include <QTableWidget>
#include <QMessageBox>
#include <stdio.h>
#include <cmath>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "error.h"
#include "func.h"
#include "matrix.h"
#include "spline.h"

double func(double x)
{
	return pow(x - 5, 3);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	plist = nullptr;
	x = 0;
	n = 0;
	
	ui->funcLabel->setText("y(x) = x * x");
}

MainWindow::~MainWindow()
{
    delete ui;
	clear_matrix(plist, n);
}

void MainWindow::on_genButton_released()
{
    file_func(-20, 5, 1, func);
}

void MainWindow::on_loadButton_released()
{
	FILE *fin = fopen("data.txt", "r");
	if (!fin)
	{
		QMessageBox::critical(this, "Ошибка", "Невозможно открыть файл!");
		return;
	}
	plist = read_matrix(fin, &n);
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
	if (n < 2)
	{
		QMessageBox::critical(this, "Ошибка", "Задайте больше одной точки!");
		return;
	}
	
	bool correct = true;
	QString xstr = ui->xEdit->text();
	double x = xstr.toDouble(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка", "Некорректное значение x!");
		return;
	}
	
	double y = solve(plist, x, n - 1);
	
	ui->yBox->setText(QString::number(y));
}

void MainWindow::data_to_table()
{
	QTableWidget *t = ui->pointTable;
	double x, y;
	for (int i = 0; i < n; i++)
	{
		x = plist[i][0];
		y = plist[i][1];
		t->insertRow(i);
		QTableWidgetItem *xitem = new QTableWidgetItem(QString::number(x));
		QTableWidgetItem *yitem = new QTableWidgetItem(QString::number(y));
		t->setItem(i, 0, xitem);
		t->setItem(i, 1, yitem);
	}
}

void MainWindow::table_clear()
{
	while (ui->pointTable->rowCount() > 0)
		ui->pointTable->removeRow(0);
}
