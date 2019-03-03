#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_enter_clicked()
{
    int check = 0;
    if (ui->lineEditX->text() == NULL && ui->lineEditY->text() == NULL)
    {
        QMessageBox::critical(this, "Ошибка","Необходимо"
                                   " ввести координаты X и Y!");
        return;
    }
    if (ui->lineEditX->text() == NULL && ui->lineEditY->text() != NULL)
    {
        QMessageBox::critical(this, "Ошибка","Необходимо"
                                   " ввести координату X!");
        return;
    }
    if (ui->lineEditX->text() != NULL && ui->lineEditY->text() == NULL)
    {
        QMessageBox::critical(this, "Ошибка","Необходимо"
                                   " ввести координату Y!");
        return;
    }
    QString x_str = ui->lineEditX->text();
    QString y_str = ui->lineEditY->text();
    check = check_point(x_str);
    if (check == -1)
    {
        QMessageBox::critical(this, "Ошибка","Неккоректная"
                                   " координата X!");
        return;
    }
    check =check_point(y_str);
    if (check == -1)
    {
        QMessageBox::critical(this, "Ошибка","Неккоректная"
                                   " координата Y!");
        return;
    }

    float x_fl = x_str.toFloat();
    float y_fl = y_str.toFloat();

    insert_into_table(x_str, y_str);
    ui->lineEditX->clear();
    ui->lineEditY->clear();
}
