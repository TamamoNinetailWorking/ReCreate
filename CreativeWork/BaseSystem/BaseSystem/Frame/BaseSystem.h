#pragma once

#include <functional>
#include <Singleton/Singleton.h>

#pragma comment (lib,"CWindow.lib")

class CWINDOW;

class CBaseSystem : public CSingleton<CBaseSystem>
{
protected:

	friend class CSingleton<CBaseSystem>;
	CBaseSystem();
	CWINDOW* m_pWindowInstance;

	std::function<void()> m_fAppFunction;

public:


	~CBaseSystem();
	void SetWindow(CWINDOW*& _pWindowInstance);
	CWINDOW*& GetWindow();

	void SetAppFunction(const std::function<void()>& _fAppFunction);

	void SystemLoop();
	void SystemApp();

};

inline CBaseSystem& GetSystem()
{
	return CBaseSystem::GetInstance();
}