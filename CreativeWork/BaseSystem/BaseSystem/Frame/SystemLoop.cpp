#include "BaseSystem.h"
#include <CWindow.h>

void CBaseSystem::SetAppFunction(const std::function<void()>& _fAppFunction)
{
	m_fAppFunction = _fAppFunction;
}

void CBaseSystem::SystemApp()
{
	m_fAppFunction();
}

void CBaseSystem::SystemLoop()
{
	m_pWindowInstance->MessageStructInit();

	//MessageLoop
	while (m_pWindowInstance->IsLoop())
	{
		if (!m_pWindowInstance->CheckPeekMessage())
		{
			SystemApp();
		}
	}

}