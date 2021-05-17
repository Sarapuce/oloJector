#include "injector.h"
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

void Injector::loadProcess()
{
	char processName[128];

	std::cout << "Target PID ? : ";
	std::cin >> m_pid;
	m_process = OpenProcess(PROCESS_ALL_ACCESS, false, m_pid);
	if (!m_process)
	{
		std::cout << "\nFailed to load process " << m_pid;
		exit(1);
	}
	std::cout << "\nProcess loaded";
}

void Injector::inject()
{
	HMODULE hkernel32 = GetModuleHandle(L"kernel32.dll");
	if (!hkernel32)
	{
		std::cout << "Impossible to load kernel32";
		exit(1);
	}

	LPVOID addr = (LPVOID)GetProcAddress(hkernel32, "LoadLibraryA");
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

	printf("Pointeur : %p", distantDllName);
}