#include "CWindow.h"

LRESULT CWINDOW::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg)
	{
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
					DestroyWindow(hWnd);
					break;
			}
			break;
			
		case WM_DESTROY:
			PostQuitMessage(0);
			CloseConsoleWindow();
			break;

		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}