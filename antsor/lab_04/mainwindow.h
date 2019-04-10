#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

double f_cos(double x);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void on_loadButton_released();
	
	void on_solveButton_released();
	
private:
    Ui::MainWindow *ui;
	
	double **plist;
	int plist_size, n;
	
	void data_to_table();
	void table_clear();
};

#endif // MAINWINDOW_H
