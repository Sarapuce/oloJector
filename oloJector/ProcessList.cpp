#include "ProcessList.h"

ProcessList::ProcessList()
{
    m_nbOfProcess = 0;
    setSystemArch();
}

bool ProcessList::refreshProcessList()
{
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    m_nbOfProcess = 0;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        qDebug() << "CreateToolhelp32Snapshot failed";
        exit(1);
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32))
    {
        qDebug() << "Process32First failed";
        CloseHandle(hProcessSnap);
        exit(1);
    }

    do
    {
        ProcessInfo p(pe32.th32ProcessID, QString::fromWCharArray(pe32.szExeFile));
        m_processes[m_nbOfProcess] = p;
        m_nbOfProcess++;
    } while (Process32Next(hProcessSnap, &pe32) && m_nbOfProcess < 1024);

    CloseHandle(hProcessSnap);

    return true;
}

void ProcessList::printList()
{
    qDebug() << "System arch : " << m_systemArch << m_nbOfProcess;
    
    for (unsigned int i = 0; i < m_nbOfProcess; i++)
        m_processes[i].printInfo();
}

void ProcessList::setSystemArch()
{
    SYSTEM_INFO si; 
    GetNativeSystemInfo(&si);

    m_systemArch = !(si.wProcessorArchitecture == 0);
}

ProcessInfo* ProcessList::getProcesses()
{
    return m_processes;
}

UINT ProcessList::getNbOfProcess()
{
    return m_nbOfProcess;
}
