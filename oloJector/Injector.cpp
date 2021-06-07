#include "Injector.h"
#include <Psapi.h>

Injector::Injector()
{
	m_dll = new dllManager();
	m_pid = 0;
	m_process = NULL;
}

void Injector::setDll()
{
	m_dll->setPath("C:\\main.dll");
	m_dll->print();
}

void Injector::loadProcess(int pid)
{
    m_pid = pid;
	m_process = OpenProcess(PROCESS_ALL_ACCESS, false, m_pid);
	if (!m_process)
	{
		std::cout << "\nFailed to load process " << m_pid;
		exit(1);
	}
	std::cout << "\nProcess loaded\n";
}

void Injector::inject()
{
	ProcessInfo pinfo(m_pid);
	pinfo.setis64();

	if (pinfo.getis64() ^ m_dll->getArch())
	{
		std::cout << "Architecture mismatch : Process : " << pinfo.getis64() << " | dll : " << m_dll->getArch();
		exit(1);
	}

	HMODULE hkernel32 = GetModuleHandle(L"kernel32.dll");
	if (!hkernel32)
	{
		std::cout << "Impossible to load kernel32";
		exit(1);
	}

	LPVOID loadLibrairyaddr = (LPVOID)GetProcAddress(hkernel32, "LoadLibraryA");
	LPVOID distantDllName = (LPVOID)VirtualAllocEx(m_process, NULL, strlen(m_dll->getPath()), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (!distantDllName)
	{
		std::cout << "Impossible de allocate memory in target";
		exit(1);
	}

	int nbBytes = WriteProcessMemory(m_process, 
									 distantDllName, 
									 m_dll->getPath(), 
									 strlen(m_dll->getPath()), 
									 NULL);

    if(!nbBytes)
    {
        std::cout << "WriteProssMemory failed";
        exit(1);
    }

	printf("Pointeur : %p\n", distantDllName);

	HANDLE threadID = CreateRemoteThread(
		m_process, 
		NULL, 
		0, 
		(LPTHREAD_START_ROUTINE)loadLibrairyaddr, 
		distantDllName, 
		NULL, 
        NULL);

	if (!threadID)
	{
		std::cout << "Impossible to start a thread in the selected process";
		exit(1);
	}

	CloseHandle(m_process);
	CloseHandle(threadID);
}
