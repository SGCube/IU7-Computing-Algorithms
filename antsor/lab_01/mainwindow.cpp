#include <QTableWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "interpol.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    QString xstr = ui->xEdit->text();
	QString ystr = ui->yEdit->text();
	// координаты точки
	float x, y;
	x = xstr.toFloat(&correct);
	if (!correct)
	{
		error_valmsg(ui->msgFrame, 0);
		return;
	}
	y = ystr.toFloat(&correct);
	if (!correct)
	{
		error_valmsg(ui->msgFrame, 1);
		return;
	}
	
	xstr = QString::number(x);
	ystr = QString::number(y);
	
	ui->xEdit->clear();
	ui->yEdit->clear();
	
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
    for (int k = ui->pointTable->rowCount(); k > 0; k--)
        ui->pointTable->removeRow(ui->pointTable->rowCount() - 1);
}

void MainWindow::on_delButton_released()
{
    ui->pointTable->removeRow(ui->pointTable->currentRow());
}
