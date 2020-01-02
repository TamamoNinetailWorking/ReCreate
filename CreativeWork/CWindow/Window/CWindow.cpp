#include "CWindow.h"

HRESULT CWINDOW::WNDC_initialize(const HINSTANCE hInstance,const LPCSTR name) 
{
	WNDCLASSEX wcex;
	wcex.hInstance = hInstance;//�C���X�^���X�l�̃Z�b�g
	wcex.lpszClassName = name;//�N���X��
	wcex.lpfnWndProc = (WNDPROC)WndProc;//�E�B���h�E���b�Z�[�W
	wcex.style = 0;//�E�B���h�E�X�^�C��
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);//���[�W�A�C�R��
	wcex.hIconSm = LoadIcon((HINSTANCE)NULL, IDI_WINLOGO);//�X���[���A�C�R��
	wcex.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);//�J�[�\���X�^�C��
	wcex.lpszMenuName = 0;//���j���[�Ȃ�
	wcex.cbClsExtra = 0;//�G�L�X�g���Ȃ�
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//�w�i�F��

	if (!RegisterClassEx(&wcex)) {
		return FALSE;
	}else{
		return S_OK;
	}
}

HRESULT CWINDOW::HWND_initialize(const HINSTANCE hInstance, const LPCSTR name, const LPCSTR title,const bool full_screen)
{
	if (full_screen){//�t���X�N���[��
		m_hWnd = CreateWindow(
			name,//�E�B���h�E�N���X�̖��O
			title,//�^�C�g��
			WS_VISIBLE | WS_POPUP,//�E�B���h�E�X�^�C��
			0, 0,//�E�B���h�E�ʒu �c�A��
			m_width, m_height,//�E�B���h�E�T�C�Y
			NULL,//�e�E�B���h�E�Ȃ�
			(HMENU)NULL,//���j���[�Ȃ�
			hInstance,//�C���X�^���X�n���h��
			(LPVOID)NULL//�ǉ������Ȃ�
		);
	}//�t���X�N���[��End
	else 
	{//�E�B���h�E���[�h
		RECT rWindow, rClient;
		int width = m_width, height = m_height;

		m_hWnd = CreateWindow(
			name,//�E�B���h�E�N���X�̖��O
			title,//�^�C�g��
			WS_CAPTION | WS_SYSMENU,//�E�B���h�E�X�^�C��
			0, 0,//�E�B���h�E�ʒu �c�A���i���ƂŒ����Ɉړ�������
			m_width, m_height,//�E�B���h�E�T�C�Y
			HWND_DESKTOP,//�e�E�B���h�E�Ȃ�
			(HMENU)NULL,//���j���[�Ȃ�
			hInstance,//�C���X�^���Â͂�ǂ�
			(LPVOID)NULL//�ǉ������Ȃ�
		);

		//�E�B���h�E�T�C�Y���Čv�Z(Metrics�����ł̓t���[���f�U�C���ƃN���C�A���g�̈�T�C�Y���ς���Ă��܂��j
		GetWindowRect(m_hWnd, &rWindow);
		GetClientRect(m_hWnd, &rClient);
		width = (rWindow.right - rWindow.left) - (rClient.right - rClient.left) + m_width;
		height = (rWindow.bottom - rWindow.top) - (rClient.bottom - rClient.top) + m_height;
		SetWindowPos(
			m_hWnd,
			NULL,
			GetSystemMetrics(SM_CXSCREEN)/2-width/2,
			GetSystemMetrics(SM_CYSCREEN)/2-height/2,
			width-1,
			height-1,
			SWP_NOZORDER
		);
	}//�E�B���h�E���[�hEnd

	if (!m_hWnd) {
		return FALSE;
	}else {
		return S_OK;
	}
}

HRESULT CWINDOW::Create_Window(const HINSTANCE hInstance, const int nWindMode)
{
	m_hInstance = hInstance;

	//�E�B���h�E�N���X�̓o�^
	if (FAILED(WNDC_initialize(hInstance, m_window_name)))
	{
		MessageBox(m_hWnd, "ERROR!", "WNDC Error", MB_OK);
		return FALSE;
	}

	//�E�B���h�E�n���h���̓o�^
	if (FAILED(HWND_initialize(hInstance, m_window_name, m_window_title,m_full_screen_flag)))
	{
		MessageBox(m_hWnd, "ERROR!", "HWND Error", MB_OK);
		return FALSE;
	}
	CreateConsoleWindow();
	ShowWindow(m_hWnd, nWindMode);
	UpdateWindow(m_hWnd);
	return S_OK;
}

void CWINDOW::MessageStructInit()
{
	m_msg = { 0 };
}

bool CWINDOW::IsLoop()
{
	return m_msg.message != WM_QUIT;
}

bool CWINDOW::CheckPeekMessage()
{
	if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);

		return true;
	}
	
	return false;
}