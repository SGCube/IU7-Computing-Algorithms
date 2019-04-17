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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_load_clicked();
    void insert_into_table(double **matrix, int amount);

    void on_show_clicked();
    void print_plot(int n, double *c);

private:
    Ui::MainWindow *ui;
    double **table;
    int amount;
};

#endif // MAINWINDOW_H
