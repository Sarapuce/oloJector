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
    m_processList = new ProcessList();
    refreshComboBox();
}

MainWindow::~MainWindow()
{
    delete m_injector;
    delete ui;
}

void MainWindow::refreshComboBox()
{
    ui->comboBox->clear();
    m_processList->refreshProcessList();
    ProcessInfo* p = m_processList->getProcesses();
    for(unsigned int i = 0; i < m_processList->getNbOfProcess(); i++)
    {
        ui->comboBox->addItem(p[i].getName());
    }

}

void MainWindow::on_pushButton_clicked()
{
    m_injector->loadProcess(m_pid);
    m_injector->inject();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    m_pid = arg1;
    qDebug() << "m_pid set to :" << m_pid;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Open a file", "File to inject", "Dynamic Link Library (*.dll);;All Files (*)");
    path = path.replace("/", "\\");
    qDebug() << "Selected file :" << path;
    m_injector->setDll(path);
}

void MainWindow::on_comboBox_activated(int index)
{
    qDebug() << "Index selected :" << index;
    m_pid = m_processList->getProcesses()[index].getPID();
    ui->spinBox->setValue(m_pid);
}
