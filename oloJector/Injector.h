#pragma once
#include "dllManager.h"
#include <tchar.h>
#include <Windows.h>

class Injector
{
public:
	Injector();
	void setDll();

private:
	dllManager* m_dll;
};

