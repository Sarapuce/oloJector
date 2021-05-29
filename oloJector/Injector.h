#pragma once
#include "dllManager.h"
#include <tchar.h>
#include <Windows.h>
#include "ProcessInfo.h"

class Injector
{
public:
	Injector();
	void setDll();
	void loadProcess();
	void inject();

private:
	HANDLE m_process;
	dllManager* m_dll;
	int m_pid;
};

