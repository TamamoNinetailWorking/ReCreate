#pragma once

#include <map>
#include <string>
#include <Singleton/Singleton.h>

typedef unsigned int UINT;
class CObject;

class CObjectManager : public virtual CSingleton<CObjectManager>
{
	friend class CSingleton<CObjectManager>;
	friend class CObject;
protected:

	UINT m_nIdCounter;
	std::map<UINT,CObject*> m_pObjectList;


	UINT CountID();
	UINT SetObject(CObject* const object);

public:

	virtual ~CObjectManager();

	void Init();
	void Exit();

	CObject*& GetObject(UINT id);
	CObject* const GetObject(std::string name);
};

inline CObjectManager& ObjectManager()
{
	return CObjectManager::GetInstance();
}