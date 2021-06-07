#pragma once
#include <Windows.h>
#include <tchar.h>
#include <psapi.h>
#include <iostream>
#include <dbghelp.h>
#include <QDebug>


class ProcessInfo
{
public:
	ProcessInfo();
    ProcessInfo(DWORD pid);
    ProcessInfo(DWORD pid, QString name);

    void setProcessName();
    void printInfo();
	void setPid(DWORD pid);
	bool isUnknow();
	bool getis64();
    void setis64();

private:
    QString m_name;
	DWORD m_pid;
	BOOL m_is64;
};

