#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <Windows.h>
#include "ProcessInfo.h"
#include "ProcessList.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pid = 0;
    m_injector = new Injector();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    m_injector->setDll();
    m_injector->loadProcess(m_pid);
    m_injector->inject();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    m_pid = arg1;
    qDebug() << m_pid;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Open a file", "File to inject", "Dynamic Link Library (*.dll);;All Files (*)");
    qDebug() << "Selected file : " << path;
}
