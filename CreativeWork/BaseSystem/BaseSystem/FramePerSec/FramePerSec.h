#pragma once

#include <windows.h>
#include <Singleton/Singleton.h>

class CFPSManager : public CSingleton<CFPSManager>
{
protected:
	
	friend class CSingleton<CFPSManager>;

	int m_nSecond;//1s
	float m_fFPS;
	DWORD m_nMeasurePoint;//time_measure_point

	HWND m_hwnd;
	LPCSTR m_windowName;

	UINT m_nResolution;

	DWORD m_nExecLastTime;
	DWORD m_nFpsLastTime;
	DWORD m_nCurrentTime;
	int m_nCountFrame;
	float m_fCountFPS;

	void begin(UINT period);
	void end();


public:

	void Init(
		HWND hwnd,
		LPCSTR window_name,
		UINT frameRate = 60,
		int second = 1000,
		DWORD measure_point = 1000,
		float count_fps = 0.0f, 
		UINT resolution = 1);

	void Exit();

	void ReadyTime();
	bool CheckTime();
	void UpdateTime();
	void Measurement_FPS();

	void DrawWindowBezel();

};

inline CFPSManager& GetFPSManager()
{
	return CFPSManager::GetInstance();
}