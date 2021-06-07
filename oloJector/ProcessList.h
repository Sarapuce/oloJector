#pragma once
#include "ProcessInfo.h"
#include <psapi.h>
#include <tlhelp32.h>
#include <sysinfoapi.h>

class ProcessList
{
public:
	ProcessList();
    bool refreshProcessList();
	void printList();
    void setSystemArch();

private:
    UINT m_nbOfProcess;
	ProcessInfo m_processes[1024];
    bool m_systemArch;
};

