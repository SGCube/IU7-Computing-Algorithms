#include <QFileDialog>
#include <fstream>

#include "window.h"
#include "ui_window.h"

#include "derivator.h"
#include "func.hpp"

Window::Window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Window)
{
	ui->setupUi(this);
	
	ui->xyTable->horizontalHeader()->setVisible(true);
	ui->resTable->horizontalHeader()->setVisible(true);
}

Window::~Window()
{
	delete ui;
}

void Window::fillTable()
{
	double x, y;
	for (size_t i = 0; i < plist.size(); i++)
	{
		x = plist[i].x;
		y = plist[i].y;
		
		ui->xyTable->insertRow(i);
		QTableWidgetItem *xitem = new QTableWidgetItem(QString::number(x));
		QTableWidgetItem *yitem = new QTableWidgetItem(QString::number(y));
		
		ui->xyTable->setItem(i, 0, xitem);
		ui->xyTable->setItem(i, 1, yitem);
		
		ui->resTable->insertRow(i);
		for (size_t j = 0; j < 6; j++)
		{
			QTableWidgetItem *item = new QTableWidgetItem("");
			ui->resTable->setItem(i, j, item);
		}
	}
}

void Window::clearTable()
{
	while (ui->xyTable->rowCount() > 0)
	{
		ui->xyTable->removeRow(0);
		ui->resTable->removeRow(0);
	}
}

void Window::on_loadButton_released()
{
	QString filePath = QFileDialog::getOpenFileName(this, "Load data", "",
													"Text file (*.txt)");
	if (filePath.isEmpty())
		return;

	std::string str = filePath.toStdString();	
	const char* fileName = str.c_str();
	
	std::ifstream fin;
	fin.open(fileName, std::fstream::in);
	plist.loadFromFile(fin);
	fin.close();
	
	clearTable();
	fillTable();
}

void Window::on_doButton_released()
{	
    for (size_t i = 0; i < plist.size(); i++)
	{
		double result;
		
		if (i == 0)
			result = Derivator::diff_right(plist, 0);
		else
			result = Derivator::diff_left(plist, i);
		ui->resTable->item(i, 0)->setText(QString::number(result));
		
		if (i == 0)
		{
			result = Derivator::raise_exp_left(plist);
			ui->resTable->item(i, 1)->setText(QString::number(result));
		}
		else if (i == plist.size() - 1)
		{
			result = Derivator::raise_exp_right(plist);
			ui->resTable->item(i, 1)->setText(QString::number(result));
		}
		
		if (0 < i && i < plist.size() - 1)
		{
			result = Derivator::diff_center(plist, i);
			ui->resTable->item(i, 2)->setText(QString::number(result));
		}
		
		if (i < plist.size() - 2)
		{
			result = Derivator::diff_runge(plist, i, 1);
			ui->resTable->item(i, 3)->setText(QString::number(result));
		}
		else
		{
			result = Derivator::diff_runge_l(plist, i, 1);
			ui->resTable->item(i, 3)->setText(QString::number(result));
		}
		
		result = Derivator::diff_level(plist, i, RealFunc::a0, RealFunc::a1);
		ui->resTable->item(i, 4)->setText(QString::number(result));
		
		result = RealFunc::diff_real(plist[i].x);
		ui->resTable->item(i, 5)->setText(QString::number(result));
	}
}
