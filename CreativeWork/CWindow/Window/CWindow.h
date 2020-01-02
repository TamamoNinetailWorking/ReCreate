#pragma once

#include <Windows.h>

#pragma comment(lib,"winmm.lib")

class CWINDOW
{
private:

	const char* m_window_name;//�E�B���h�E��
	const char* m_window_title;//�E�B���h�E�^�C�g��
	const int m_timer_resolution;//�^�C�}�[�̕���\
	const int m_frame_max;//�t���[���ő�l
	const int m_frame_per_second;//�P�t���[��������̏�������
	bool m_full_screen_flag;//�t���X�N���[���ݒ�

	HWND m_hWnd;//�E�B���h�E�n���h��
	MSG m_msg;//���b�Z�[�W
	int m_width;//�E�B���h�E�̉���
	int m_height;//�E�B���h�E�̍���
	HINSTANCE m_hInstance;//�E�B���h�E�\����
	int m_timer_id;//�^�C�}�[ID
	int m_hConsole;//�R���\�[���E�B���h�E�̃n���h��

	HRESULT WNDC_initialize(const HINSTANCE hInstance,const LPCSTR name);
	HRESULT HWND_initialize(const HINSTANCE hInstance, const LPCSTR name, const LPCSTR title,const bool full_screen);

public:

	CWINDOW()//�f�t�H���g�R���X�g���N�^
		:m_window_name("WinApp"),
		m_window_title("Shader Tester"),
		m_full_screen_flag(false),
		m_width(1280),
		m_height(720),
		m_timer_resolution(1),
		m_frame_max(60),
		m_frame_per_second(1000/m_frame_max),
		m_hConsole(0){};//�萔�l�̏�����
	~CWINDOW() {};//�f�X�g���N�^

	HRESULT Create_Window(const HINSTANCE hInstance, const int nWindMode);

	void CreateConsoleWindow();
	void CloseConsoleWindow();

	LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void MessageStructInit();

	bool IsLoop();
	bool CheckPeekMessage();

	void Loop();//���b�Z�[�W���[�v

	HINSTANCE GetHinstance() { return m_hInstance; };
	HWND GetHWND() { return m_hWnd; };
	MSG GetMSG() { return m_msg; };
	int GetWindowWidth() { return m_width; };
	int GetWindowHeight() { return m_height; };

};

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);