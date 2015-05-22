#include "mainwindow.h"
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    MainWidget* mainWgt = new MainWidget;

    setCentralWidget( mainWgt);
}

MainWindow::~MainWindow()
{

}

