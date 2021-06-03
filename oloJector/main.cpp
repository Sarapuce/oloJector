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
    std::cout << "AstraPfizer1!\n";
    ProcessList* lp = new ProcessList();
    lp->refreshProcess();
    lp->printList();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
