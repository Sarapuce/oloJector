#include "mainwindow.h"
#include <iostream>
#include <Windows.h>
#include "ProcessInfo.h"
#include "ProcessList.h"
#include "Injector.h"

#include <QApplication>
#include <QtDebug>

int main(int argc, char *argv[])
{
    std::cout << "oloJector v0.0.1\n";
    ProcessInfo pi(3404);
    pi.printInfo();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
