#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::StartWindow)
{
	ui->setupUi(this);
	
	mainW1 = new MainWindow();
	connect(mainW1, &MainWindow::firstWindow, this, &StartWindow::show);
	
	mainW2 = new ProgWindow();
	connect(mainW2, &ProgWindow::firstWindow, this, &StartWindow::show);
}

StartWindow::~StartWindow()
{
	delete ui;
}

void StartWindow::on_pushButton_released()
{
	mainW1->show();
	this->close();
}

void StartWindow::on_pushButton_2_released()
{
	mainW2->show();
	this->close();
}
