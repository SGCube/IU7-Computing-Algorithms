#include <QTableWidget>

#include <iostream>
#include <fstream>
using namespace std;

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "interpol.h"
#include "matrix.h"
#include "error.h"
#include "func.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	plist = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_released()
{
	// флаг корректности данных
	bool correct = true;
	// строки для хранения содержимого полей ввода
    QString xstr = ui->x0Edit->text();
	QString ystr = ui->y0Edit->text();
	// координаты точки
	double x, y;
	x = xstr.toDouble(&correct);
	if (!correct)
	{
		error_msg(ui->msgFrame, ERR_VAL_X);
		return;
	}
	y = ystr.toDouble(&correct);
	if (!correct)
	{
		error_msg(ui->msgFrame, ERR_VAL_Y);
		return;
	}
	
	xstr = QString::number(x);
	ystr = QString::number(y);
	
	ui->x0Edit->clear();
	ui->y0Edit->clear();
	
	ui->pointTable->insertRow(ui->pointTable->rowCount());
	int row = ui->pointTable->rowCount() - 1;
	
	QTableWidgetItem *xitem = new QTableWidgetItem(xstr);
	QTableWidgetItem *yitem = new QTableWidgetItem(ystr);
	ui->pointTable->setItem(row, 0, xitem);
	ui->pointTable->setItem(row, 1, yitem);
	
	ui->delAllButton->setDisabled(false);
}

void MainWindow::on_delAllButton_released()
{
	while (ui->pointTable->rowCount() > 0)
		ui->pointTable->removeRow(ui->pointTable->rowCount() - 1);
	
	ui->x0Edit->clear();
	ui->y0Edit->clear();
	
	ui->delButton->setDisabled(true);
	ui->delAllButton->setDisabled(true);
}

void MainWindow::on_delButton_released()
{
	ui->pointTable->removeRow(ui->pointTable->currentRow());
	ui->pointTable->clearFocus();
	
	ui->x0Edit->clear();
	ui->y0Edit->clear();
	
	ui->delButton->setDisabled(true);
	if (ui->pointTable->rowCount() == 0)
		ui->delAllButton->setDisabled(true);
}

void MainWindow::on_solveButton_released()
{
	// флаг корректности данных
	bool correct = true;
	// строки для хранения содержимого полей ввода
    QString xstr = ui->xEdit->text();
	QString nstr = ui->nEdit->text();
	// параметр X функции
	double x;
	// степень полинома
	int n;
	
	// проверка на корректность данных
	x = xstr.toDouble(&correct);
	if (!correct)
	{
		error_msg(ui->msgFrame, ERR_VAL_X);
		return;
	}
	n = nstr.toInt(&correct);
	if (!correct || n < 1)
	{
		error_msg(ui->msgFrame, ERR_VAL_N);
		return;
	}
	
	xstr = QString::number(x);
	nstr = QString::number(n);
	
	table_to_matrix();
	double y = solve(plist, x, n, k);
	double yreal = func(x);
	
	ui->yFrame->setText(QString::number(y));
	ui->yrealFrame->setText(QString::number(yreal));
	
	clear_matrix(plist, k);
	k = 0;
}

void MainWindow::table_to_matrix()
{
	QTableWidget *t = ui->pointTable;
	k = t->rowCount();
	
	plist = new double* [k];
	if (!plist)
	{
		error_msg(ui->msgFrame, ERR_MEM);
		return;
	}
	for (int i = 0; i < k; i++)
	{
		plist[i] = new double [2];
		if (!plist[i])
		{
			clear_matrix(plist, i);
			error_msg(ui->msgFrame, ERR_MEM);
			return;
		}
	}
	
	for (int i = 0; i < k; i++)
	{
		plist[i][0] = t->item(i, 0)->text().toDouble();
		plist[i][1] = t->item(i, 1)->text().toDouble();
	}
	
	ui->delAllButton->setDisabled(false);
}

void MainWindow::matrix_to_table()
{
	QTableWidget *t = ui->pointTable;
	
	for (int i = 0; i < k; i++)
	{
		t->insertRow(i);
		QTableWidgetItem *xstr = new QTableWidgetItem(
					QString::number(plist[i][0]));
		QTableWidgetItem *ystr = new QTableWidgetItem(
					QString::number(plist[i][1]));
		t->setItem(i, 0, xstr);
		t->setItem(i, 1, ystr);
	}
	
	clear_matrix(plist, k);
	k = 0;
}

void error_msg(QLabel *msgbox, int rc)
{
	switch (rc)
	{
	case OK:
		break;
	case ERR_POINTN:
		msgbox->setText(QString("Недостаточно данных для решения задачи!"));
		break;
	case ERR_MEM:
		msgbox->setText(QString("Ошибка выделения памяти!"));
		break;
	case ERR_VAL_X:
		msgbox->setText(QString("Некорректная координата X!"));
		break;
	case ERR_VAL_Y:
		msgbox->setText(QString("Некорректная координата Y!"));
		break;
	case ERR_FILE:
		msgbox->setText(QString("Ошибка чтения!"));
		break;
	default:
		msgbox->setText(QString("Неизвестная ошибка!"));
		break;
	}
}


void MainWindow::on_loadButton_released()
{
	ifstream fin("data.txt");
	if (!fin.is_open())
	{
		error_msg(ui->msgFrame, ERR_FILE);
		return;
	}
	int new_k = 0;
	double **new_plist = read_matrix(fin, &new_k);
	fin.close();
	if (!new_plist)
	{
		error_msg(ui->msgFrame, ERR_FILE);
		return;
	}
	clear_matrix(plist, k);
	plist = new_plist;
	k = new_k;
	matrix_to_table();
}
