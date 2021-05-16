#include "ProcessList.h"

ProcessList::ProcessList()
{
    m_nbOfProcess = 0;
    setis64();
}

bool ProcessList::refreshProcess()
{
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    m_nbOfProcess = 0;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        std::wcout << TEXT("CreateToolhelp32Snapshot failed\n");
        return false;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32))
    {
        std::wcout << TEXT("Process32First failed\n");
        CloseHandle(hProcessSnap);
        return false;
    }

    do
    {
        ProcessInfo p(pe32.th32ProcessID, pe32.szExeFile);
        p.setis64();
        m_processes[m_nbOfProcess] = p;
        m_nbOfProcess++;
    } while (Process32Next(hProcessSnap, &pe32) && m_nbOfProcess < 1024);

    CloseHandle(hProcessSnap);

    return true;
}

void ProcessList::printList()
{
    wprintf(TEXT("Architecture : %d\n"), m_is64);
    
    for (unsigned int i = 0; i < m_nbOfProcess; i++)
        m_processes[i].printInfo(m_is64);
}

void ProcessList::setis64()
{
    SYSTEM_INFO si; 
    GetNativeSystemInfo(&si);

    m_is64 = !(si.wProcessorArchitecture == 0);
}