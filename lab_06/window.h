#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

#include "pointlist.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit Window(QWidget *parent = nullptr);
	~Window();
	
private slots:
	void on_loadButton_released();
	
	void on_doButton_released();
	
private:
	Ui::Window *ui;
	PointList plist;
	
	void fillTable();
	void clearTable();
};

#endif // WINDOW_H
