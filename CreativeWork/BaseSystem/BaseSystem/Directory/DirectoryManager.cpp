#include "DirectoryManager.h"
#include <Windows.h>

CDirectoryManager::~CDirectoryManager()
{
	Exit();
}

void CDirectoryManager::Init(UINT name_size)
{
	m_directory_name_size = name_size;
	m_default_current_directory = new char[m_directory_name_size];

	GetCurrentDirectory(m_directory_name_size, m_default_current_directory);
}

void CDirectoryManager::Exit()
{
	delete[] m_default_current_directory;
}

void CDirectoryManager::RestoreDefaultDirectory()
{
	SetCurrentDirectory(m_default_current_directory);
}

void CDirectoryManager::SetDirectory(const char* directory)
{
	SetCurrentDirectory(directory);
}