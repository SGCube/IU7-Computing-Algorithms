#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

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
    void on_addButton_released();

    void on_delAllButton_released();

    void on_delButton_released();

    void on_drawButton_released();

	void on_clearButton_released();
	
	void on_solveButton_released();
	
	void on_loadButton_released();
	
private:
    Ui::MainWindow *ui;
	
	double **plist;
	int k;
	void table_to_matrix();
	void matrix_to_table();
};

void error_msg(QLabel *msgbox, int rc);

#endif // MAINWINDOW_H
