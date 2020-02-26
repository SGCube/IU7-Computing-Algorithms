#ifndef PROGWINDOW_H
#define PROGWINDOW_H

#include <QMainWindow>

double f(double x);

namespace Ui {
class ProgWindow;
}

class ProgWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit ProgWindow(QWidget *parent = 0);
	~ProgWindow();
	
signals:
    void firstWindow();
	
private slots:
	void on_pushButton_released();
	
private:
	Ui::ProgWindow *ui;
	
	double **plist;
	int n;
	
	void table_swap();
};

#endif // PROGWINDOW_H
