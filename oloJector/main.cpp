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
    qDebug() << "oloJector v0.0.1";
    dllManager* dll = new dllManager();
    dll->loadDll("C:\\Users\\olo76\\source\\repos\\messageBox\\x64\\Debug\\messageBox.dll");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
