#include "ProcessInfo.h"

ProcessInfo::ProcessInfo()
{
	m_pid = 0;
	_tcscpy_s(m_name, MAX_PATH, _T("<unknow>"));
    m_is64 = false;
}

ProcessInfo::ProcessInfo(DWORD pid)
{
	m_pid = pid;
	_tcscpy_s(m_name, MAX_PATH, _T("<unknow>"));
    m_is64 = false;
}

ProcessInfo::ProcessInfo(DWORD pid, const TCHAR* name)
{
    m_pid = pid;
    _tcscpy_s(m_name, MAX_PATH, name);
    m_is64 = false;
}

int ProcessInfo::getProcessName()
{
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, m_pid);
    if (NULL != hProcess)
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if (EnumProcessModulesEx(hProcess, &hMod, sizeof(hMod), &cbNeeded, LIST_MODULES_ALL))
        {
            GetModuleBaseName(hProcess, hMod, m_name, sizeof(m_name) / sizeof(TCHAR));
        }
        return 0;
    }
    return 1;
}

void ProcessInfo::printInfo()
{
    wprintf(TEXT("%-50s | PID : %u\n"), m_name, m_pid);
}

void ProcessInfo::printInfo(bool is64)
{
    TCHAR arch[4];
    if (m_is64)
        _tcscpy_s(arch, 4, TEXT("x86"));
    else if (is64)
        _tcscpy_s(arch, 4, TEXT("x64"));
    else
        _tcscpy_s(arch, 4, TEXT("x86"));

    wprintf(TEXT("%-50s | PID : %-6u | Architecture : %s\n"), m_name, m_pid, arch);
}

bool ProcessInfo::isUnknow()
{
    return wcscmp(m_name, _T("<unknow>")) == 0;
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
        m_is64 = bIsWow64;
    }
    CloseHandle(processHandle);
}