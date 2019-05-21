#include <QFileDialog>
#include <fstream>

#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Window)
{
	ui->setupUi(this);
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
	}
}

void Window::clearTable()
{
	while (ui->xyTable->rowCount() > 0)
		ui->xyTable->removeRow(0);
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
    
}
