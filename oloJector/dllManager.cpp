#include "dllManager.h"

dllManager::dllManager()
{
    m_path = "";
	m_is64 = false;
	m_length = 0;
}

QString dllManager::getPath()
{
    return m_path;
}

void dllManager::setPath(QString path)
{
    m_path = path;
}

void dllManager::loadDll(QString path)
{

    QByteArray x64 = "\x64\x86";
    QByteArray x86 = "\x4c\x01";
    QByteArray buffer;

    setPath(path);
    QFile file(m_path);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Impossible to open :" << m_path;
        exit(1);
    }

    buffer = file.read(512);

    if(buffer.contains(x86))
    {
        m_is64 = false;
        qDebug() << "dll arch : x86";
    }

    else if(buffer.contains(x64))
    {
        m_is64 = true;
        qDebug() << "dll arch : x64";
    }

    else
    {
        qDebug() << "Not a valid dll";
        exit(1);
    }
}

void dllManager::print()
{
    QString arch;
	if (m_is64)
        arch = "x64";
	else
        arch = "x86";

    qDebug() << "Dll loaded :" << m_path << "| Arch : " << arch;
}

bool dllManager::getArch()
{
	return m_is64;
}
