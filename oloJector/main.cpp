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
    qDebug() << "oloJector v0.0.1";
    ProcessList* l = new ProcessList();
    l->refreshProcessList();
    l->printList();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
