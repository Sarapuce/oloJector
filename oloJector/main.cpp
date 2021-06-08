#include "mainwindow.h"
#include <iostream>
#include <Windows.h>
#include "ProcessInfo.h"
#include "ProcessList.h"
#include "Injector.h"
#include "dllManager.h"

#include <QApplication>
#include <QtDebug>

int main(int argc, char *argv[])
{
    qDebug() << "oloJector v1.0.1";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
