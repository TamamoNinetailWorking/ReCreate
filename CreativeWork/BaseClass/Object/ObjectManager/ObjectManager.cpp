#include "ObjectManager.h"
#include <Object/Base/Object.h>

UINT CObjectManager::CountID()
{
	UINT temp = m_nIdCounter;
	m_nIdCounter++;
	return temp;
}

UINT CObjectManager::SetObject(CObject* object)
{
	UINT count = CountID();
	m_pObjectList[count] = object;
	return count;
}

CObjectManager::~CObjectManager()
{
	Exit();
}

void CObjectManager::Init()
{
	m_nIdCounter = 0;
}

void CObjectManager::Exit()
{
	for (auto mp : m_pObjectList)
	{
		delete mp.second;
	}
	m_pObjectList.clear();
}

CObject*& CObjectManager::GetObject(UINT id)
{
	return m_pObjectList[id];
}

CObject* const CObjectManager::GetObject(std::string name)
{
	for (auto mp : m_pObjectList)
	{
		if (name == mp.second->GetObjectName())
		{
			return mp.second;
		}
	}
	return nullptr;
}