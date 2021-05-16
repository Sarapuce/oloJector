#pragma once
#include <Windows.h>
#include <tchar.h>
#include <psapi.h>
#include <iostream>
#include <dbghelp.h>

class ProcessInfo
{
public:
	ProcessInfo();
	ProcessInfo(DWORD pid);
	ProcessInfo(DWORD pid, const TCHAR* name);

	int getProcessName();
	void printInfo();
	void printInfo(bool is64);
	void setPid(DWORD pid);
	bool isUnknow();
	bool getis64();
	void setis64();

private:
	TCHAR m_name[MAX_PATH];
	DWORD m_pid;
	BOOL m_is64;
};

