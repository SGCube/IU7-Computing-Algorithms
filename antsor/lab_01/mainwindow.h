#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
	
	void on_genButton_released();
	
	void on_loadButton_released();
	
	void on_solveButton_released();
	
private:
    Ui::MainWindow *ui;
	
	double **plist;
	int k;
	double x;
	int n;
	
	void data_to_table();
	void table_clear();
};

#endif // MAINWINDOW_H
