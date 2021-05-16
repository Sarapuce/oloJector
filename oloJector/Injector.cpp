#include "injector.h"

Injector::Injector()
{
	m_dll = new dllManager();
}

void Injector::setDll()
{
	m_dll->setPath(_T("C:\\main.dll"));
	m_dll->print();
}