#include "BaseSystem.h"
#include <CWindow.h>

CBaseSystem::CBaseSystem() : CSingleton()
{

}

CBaseSystem::~CBaseSystem()
{

}

void CBaseSystem::SetWindow(CWINDOW*& _pWindowInstance)
{
	m_pWindowInstance = _pWindowInstance;
}

CWINDOW*& CBaseSystem::GetWindow()
{
	return m_pWindowInstance;
}