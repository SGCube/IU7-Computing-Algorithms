#include <QMessageBox>
#include <cmath>

#include "progwindow.h"
#include "ui_progwindow.h"

#include "func.h"
#include "matrix.h"
#include "interpol.h"

double f(double x)
{
	return cos(x) + x;
}

ProgWindow::ProgWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::ProgWindow)
{
	ui->setupUi(this);
	
	ui->funcLabel->setText("y(x) = cos(x) + x");
}

ProgWindow::~ProgWindow()
{
	delete ui;
	
	emit firstWindow();
}

void ProgWindow::on_pushButton_released()
{
	bool correct = true;

	QString astr = ui->aEdit->text();
	QString bstr = ui->bEdit->text();
	QString stepstr = ui->stepEdit->text();
	
	double a = astr.toDouble(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение левой границы интервала!");
		return;
	}
	
	double b = bstr.toDouble(&correct);
	if (!correct)
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение правой границы интервала!");
		return;
	}
	
	double step = stepstr.toDouble(&correct);
	if (!correct || step == 0 || (step < 0 && a < b) || (step > 0 && a > b))
	{
		QMessageBox::critical(this, "Ошибка",
							  "Некорректное значение шага!");
		return;
	}
	
	file_func(a, b, step, f);
	
	FILE *fin = fopen("data.txt", "r");
	if (!fin)
	{
		QMessageBox::critical(this, "Ошибка", "Невозможно открыть файл!");
		return;
	}
	plist = read_matrix(fin, &n);
	if (!plist)
	{
		QMessageBox::critical(this, "Ошибка", "Ошибка чтения таблицы!");
		fclose(fin);
		return;
	}
	table_swap();
	
	double x0 = solve(plist, 0, n - 1, n);
	ui->xBox->setText(QString::number(x0));
	
	clear_matrix(plist, n);
	n = 0;
	fclose(fin);
}

void ProgWindow::table_swap()
{
	if (plist)
		for (int i = 0; i < n; i++)
		{
			double tmp = plist[i][0];
			plist[i][0] = plist[i][1];
			plist[i][1] = tmp;
		}
}
