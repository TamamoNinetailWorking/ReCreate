#include <Windows.h>
#include <BaseSystem/Frame/BaseSystem.h>
#include <CWindow.h>

//Procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return GetSystem().GetWindow()->MsgProc(hWnd, uMsg, wParam, lParam);
}