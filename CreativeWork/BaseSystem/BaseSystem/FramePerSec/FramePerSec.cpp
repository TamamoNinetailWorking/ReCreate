#include "FramePerSec.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

void CFPSManager::begin(UINT period)
{
	m_nResolution = period;
	timeBeginPeriod(m_nResolution);
	m_nExecLastTime = m_nFpsLastTime = timeGetTime();
	return;
}

void CFPSManager::end()
{
	timeEndPeriod(m_nResolution);
	return;
}

void CFPSManager::Init(HWND hwnd,LPCSTR window_name,UINT frameRate,int second,DWORD measure_point,float count_fps,UINT resolution)
{
	m_hwnd = hwnd;
	m_windowName = window_name;
	m_nSecond = second;
	m_fFPS = static_cast<float>(second) / static_cast<float>(frameRate);
	m_nMeasurePoint = measure_point;
	m_fCountFPS = count_fps;
	
	begin(resolution);
	
	return;
}
void CFPSManager::Exit()
{
	end();
	return;
}

void CFPSManager::ReadyTime()
{
	m_nCurrentTime = timeGetTime();
}

bool CFPSManager::CheckTime()
{
	return (m_nCurrentTime - m_nExecLastTime >= m_fFPS);
}

void CFPSManager::UpdateTime()
{
	m_nCountFrame++;
	m_nExecLastTime = timeGetTime();
	return;
}

void CFPSManager::Measurement_FPS()
{
	if (m_nCurrentTime - m_nFpsLastTime >= m_nMeasurePoint)
	{
		float DurationTime = static_cast<float>(m_nCountFrame * m_nSecond);
		float Delta = static_cast<float>(m_nCurrentTime - m_nFpsLastTime);
		m_fCountFPS = DurationTime / Delta;
		m_nFpsLastTime = m_nCurrentTime;
		m_nCountFrame = 0;
	}

	return;
}

void CFPSManager::DrawWindowBezel()
{
	std::string str;
	str = std::string(m_windowName) + std::string(" ");
	str = std::string("FPS:") + std::_Floating_to_string("%.2f",m_fCountFPS);

	SetWindowText(m_hwnd, static_cast<LPCSTR>(str.c_str()));
	return;
}