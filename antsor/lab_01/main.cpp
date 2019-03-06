#include "mainwindow.h"
#include <QApplication>
#include "func.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
	
	file_func(-2, 2, 10);
	
    w.show();

    return a.exec();
}
