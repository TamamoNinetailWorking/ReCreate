#include "CWindow.h"

void CWINDOW::Loop()
{
	m_msg = { 0 };

	//メッセージループ
	while (m_msg.message != WM_QUIT)
	{
		if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
		else
		{

		}
	}

	return;
}