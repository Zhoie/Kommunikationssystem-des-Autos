#include <QtGui/QApplication>
#include "mainwindow.h"

#include "uartwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    UartWidget w;

    w.show();

    return a.exec();
}
