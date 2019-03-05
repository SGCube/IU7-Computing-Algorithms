#include <QTableWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "interpol.h"
#include "error.h"

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
    QString xstr = ui->xtEdit->text();
	QString ystr = ui->ytEdit->text();
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
	
	ui->xtEdit->clear();
	ui->ytEdit->clear();
	
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
	
	ui->xEdit->clear();
	ui->yEdit->clear();
	
	ui->delButton->setDisabled(true);
	ui->delAllButton->setDisabled(true);
}

void MainWindow::on_delButton_released()
{
	ui->pointTable->removeRow(ui->pointTable->currentRow());
	ui->pointTable->clearFocus();
	
	ui->xEdit->clear();
	ui->yEdit->clear();
	
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
}

void MainWindow::table_to_matrix()
{
	QTableWidget *t = ui->pointTable;
	k = t->rowCount();
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
	default:
		msgbox->setText(QString("Неизвестная ошибка!"));
		break;
	}
}

