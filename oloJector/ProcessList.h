#pragma once
#include "ProcessInfo.h"
#include <psapi.h>
#include <tlhelp32.h>
#include <sysinfoapi.h>

class ProcessList
{
public:
	ProcessList();
	bool refreshProcess();
	void printList();
	void setis64();

private:
	unsigned int m_nbOfProcess;
	ProcessInfo m_processes[1024];
	bool m_is64;
};

