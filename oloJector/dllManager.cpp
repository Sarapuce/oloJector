#include "dllManager.h"

dllManager::dllManager()
{
	strcpy_s(m_path, "");
	m_is64 = false;
	m_length = 0;
}

char* dllManager::getPath()
{
	return m_path;
}

void dllManager::setPath(const char* path)
{
	char buffer[512];

	const char x86[] = { 0x02, 0x02, 0x64, 0x86, 0x00 };
	const char x64[] = { 0x02, 0x02, 0x4c, 0x01, 0x00 };
	
	strcpy_s(m_path, path);

	std::ifstream dll_file(m_path, std::ios::binary);

	if (!dll_file)
	{
		std::cout << "Impossible d'ouvrir le fichier\n";
		return;
	}

	dll_file.seekg(0, std::ios::end);
	m_length = (size_t)dll_file.tellg();
	dll_file.seekg(0, std::ios::beg);

	if (!(dll_file.read(buffer, sizeof(buffer))))
	{
		std::cout << dll_file.eof();
		std::cout << "Impossible de lire le fichier";
		return;
	}

	for (unsigned int i = 0; i < 511; i++)
	{
		if (buffer[i] == 0) 
		{
			buffer[i] = 2;
		}
	}
	buffer[511] = 0;

	dll_file.close();

	if (strstr(buffer, x86))
	{
		m_is64 = false;
		return;
	}
	
	if (strstr(buffer, x64))
	{
		m_is64 = true;
		return;
	}

	std::cout << "Not a valid dll";
}

void dllManager::print()
{
	TCHAR arch[4];
	if (m_is64)
		_tcscpy_s(arch, 4, TEXT("x64"));
	else
		_tcscpy_s(arch, 4, TEXT("x86"));

	printf("\nDll loaded : %s\nArchitecture : %ws\n", m_path, arch);
}