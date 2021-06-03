#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <Windows.h>
#include "ProcessInfo.h"
#include "ProcessList.h"
#include "Injector.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pid = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Injector* injector = new Injector();
    injector->setDll();
    injector->loadProcess(m_pid);
    injector->inject();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    m_pid = arg1;
    qDebug() << m_pid;
}
