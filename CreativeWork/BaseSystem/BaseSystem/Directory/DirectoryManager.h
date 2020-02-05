#pragma once

#include <Singleton/Singleton.h>

typedef unsigned int UINT;

class CDirectoryManager : public CSingleton<CDirectoryManager>
{
protected:

	friend class CSingleton<CDirectoryManager>;

	UINT m_directory_name_size;
	char* m_default_current_directory;

public:

	virtual ~CDirectoryManager();

	void Init(UINT name_size = 1024);
	void Exit();

	void RestoreDefaultDirectory();
	void SetDirectory(const char* directory);

};

inline CDirectoryManager& GetDirectoryManager()
{
	return CDirectoryManager::GetInstance();
}