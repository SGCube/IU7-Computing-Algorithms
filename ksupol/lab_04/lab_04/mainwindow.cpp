#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "func.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Лабораторная работа №4");

    const QStringList a = {"X", "Y", "Ro"};
    ui->table->setColumnCount(3);
    ui->table->setShowGrid(true);

    ui->table->setHorizontalHeaderLabels(a);
    ui->table->horizontalHeader()->resizeSection(0, 90);
    ui->table->horizontalHeader()->resizeSection(1, 90);
    ui->table->horizontalHeader()->resizeSection(2, 90);
    ui->table->setEditTriggers(QAbstractItemView :: NoEditTriggers);

    table = NULL;
    amount = 0;
}

MainWindow::~MainWindow()
{
    free_matrix(table);
    delete ui;
}

void MainWindow::on_load_clicked()
{
    int rc;
    FILE *f = fopen("table2_2.txt", "r");
    if (!f)
    {
        QMessageBox::critical(this, "Ошибка", "Невозможно открыть файл!");
        return;
    }
    rc = read_from_file(f, &amount, &table);
    if (rc != 0)
    {
        QMessageBox::critical(this, "Ошибка", "Невозможно считать таблицу!");
        fclose(f);
        return;
    }
    insert_into_table(table, amount);
    fclose(f);
}

void MainWindow::insert_into_table(double **matrix, int amount)
{
    for (int i = 0; i < amount; i++)
    {
        ui->table->insertRow(i);

        QTableWidgetItem *item = new QTableWidgetItem();
        QString x = QString::number(matrix[i][0]);
        item->setText(x);
        ui->table->setItem(i,0,item);

        QTableWidgetItem *item2 = new QTableWidgetItem();
        QString y = QString::number(matrix[i][1]);
        item2->setText(y);
        ui->table->setItem(i,1,item2);

        QTableWidgetItem *item3 = new QTableWidgetItem();
        QString ro = QString::number(matrix[i][2]);
        item3->setText(ro);
        ui->table->setItem(i,2,item3);
    }
}

void MainWindow::on_show_clicked()
{
    if (ui->nn->text() == NULL)
    {
        QMessageBox::critical(this, "Ошибка", "Введите степень n!");
        return;
    }
    int n = ui->nn->text().toInt();
    if (n < 0)
    {
        QMessageBox::critical(this, "Ошибка", "Введите степень n!");
        return;
    }
    double **matrix = NULL;
    double *col = (double *)calloc(n + 1, sizeof(double));
    if (!col)
    {
        QMessageBox::critical(this, "Ошибка", "Ошибка выделения памяти!");
        return;
    }
    matrix = get_slau_matrix(table, amount, n, &col);
    if (!matrix)
    {
        QMessageBox::critical(this, "Ошибка", "Ошибка выделения памяти!");
        return;
    }
    double **m;
    //if (n < amount)
    m = solve(matrix, amount, n);
    double *c;
    c = mult(m, col, n + 1);
    free(col);
    free_matrix(matrix);
    free_matrix(m);
    print_plot(n, c);
    free(c);
}

void MainWindow::print_plot(int n, double *c)
{
    QVector<double> x(101), y(101);
    double step = (table[amount - 1][0] - table[0][0])/100;
    double s = table[0][0];
    for (int i = 0; i < 101; i++)
    {
        x[i] = s;
        s += step;
    }
    for (int i = 0; i < 101; i++)
    {
        double tmp = 0;
        for (int j = 0; j < n + 1; j++)
            tmp += F(x[i], j) * c[j];
        y[i] = tmp;
    }
    double max_y = y[0];
    double min_y = y[0];
    for (int i = 0; i < 101; i++)
    {
        if (y[i] > max_y) max_y = y[i];
        if (y[i] < min_y) min_y = y[i];
    }

    QVector<double> xx(amount), yy(amount);
    for (int i = 0; i < amount; i++)
    {
        xx[i] = table[i][0];
        yy[i] = table[i][1];
    }
    ui->widget->clearGraphs();
    ui->widget->addGraph()->setData(xx, yy);
    ui->widget->graph(0)->setPen(QColor(50, 50, 50, 255));
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);

    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    ui->widget->addGraph()->setData(x, y);

    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    ui->widget->xAxis->setRange(table[0][0] - 3, table[amount - 1][0] + 3);
    ui->widget->yAxis->setRange(min_y - 5, max_y + 5);

    ui->widget->replot();
}
