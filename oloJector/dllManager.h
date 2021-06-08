#pragma once
#include <tchar.h>
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <QString>
#include <QtDebug>
#include <QFile>

class dllManager
{
public:
    dllManager();
	void print();
    QString getPath();
	bool getArch();
    void loadDll(QString path);

private:
    QString m_path;
	bool m_is64;
	size_t m_length;
};

