#include "ProcessInfo.h"

ProcessInfo::ProcessInfo()
{
	m_pid = 0;
    m_name = "<unknow>";
    m_is64 = false;
}

ProcessInfo::ProcessInfo(DWORD pid)
{
    m_pid = pid;
    setProcessName();
    getis64();
}

void ProcessInfo::setProcessName()
{
    TCHAR name[MAX_PATH];
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, m_pid);
    GetProcessImageFileName(processHandle, name, MAX_PATH);
    m_name = QString::fromWCharArray(name);
    m_name = m_name.section("\\", -1);
}

void ProcessInfo::printInfo()
{
    QString arch;

    if (m_is64)
        arch = "x64";
    else
        arch = "x86";

    qDebug() << m_name << "|" << m_pid << "|" << arch;
}

bool ProcessInfo::isUnknow()
{
    return m_name == "<unknow>";
}

void ProcessInfo::setPid(DWORD pid)
{
    m_pid = pid;
}

bool ProcessInfo::getis64()
{
    return m_is64;
}

void ProcessInfo::setis64()
{
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, m_pid);
    BOOL bIsWow64 = FALSE;

    typedef BOOL(WINAPI* LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
    LPFN_ISWOW64PROCESS fnIsWow64Process;
    HMODULE k32 = GetModuleHandle(TEXT("kernel32"));
    if (k32)
    {
        fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(k32, "IsWow64Process");

        if (NULL != fnIsWow64Process)
        {
            if (!fnIsWow64Process(processHandle, &bIsWow64))
            {

            }
        }
        m_is64 = !bIsWow64;
    }
    CloseHandle(processHandle);
}
