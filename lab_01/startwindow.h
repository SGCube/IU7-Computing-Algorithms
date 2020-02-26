#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "progwindow.h"

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit StartWindow(QWidget *parent = 0);
	~StartWindow();
	
private slots:
	void on_pushButton_released();
	
	void on_pushButton_2_released();
	
private:
	Ui::StartWindow *ui;
	
	MainWindow *mainW1;
	ProgWindow *mainW2;
};

#endif // STARTWINDOW_H
