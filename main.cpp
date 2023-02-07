#include "mainwindow.h"
#include "window.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QStringList>
#include <thread>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
