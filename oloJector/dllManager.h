#pragma once
#include <tchar.h>
#include <Windows.h>
#include <fstream>
#include <iostream>

class dllManager
{
public:
	dllManager();
	void setPath(const TCHAR* path);
	void print();
	TCHAR* getPath();

private:
	TCHAR m_path[MAX_PATH];
	bool m_is64;
	size_t m_length;
};

