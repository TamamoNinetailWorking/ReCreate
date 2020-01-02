#pragma once

#include <d3d11.h>
#include <Singleton/Singleton.h>

#pragma comment(lib,"d3d11.lib")

/* DirectX11 PrimaryDevice Class */
class CDirectGraphicsDevice : public CSingleton<CDirectGraphicsDevice>
{
	friend class CSingleton<CDirectGraphicsDevice>;
protected:

	///<Variables>///

	/* Window Config */
	HWND m_hwnd;
	int m_width, m_height;
	bool m_full_screen;

	/* Device */
	D3D_DRIVER_TYPE m_DriverType;
	D3D_FEATURE_LEVEL m_FeatureLevel;

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	IDXGISwapChain* m_pSwapChain;


	///<Functions>///

	/* Init Functions */
	HRESULT Create_Device_And_SwapChain();

public:

	virtual ~CDirectGraphicsDevice() {};

	bool Init(HWND hwnd, bool full_screen_flag, int width, int height);
	void Exit();

	ID3D11Device*& GetDevice();
	ID3D11DeviceContext*& GetImmediateContext();
	IDXGISwapChain*& GetSwapChain();

	int GetWindowWidth() const;
	int GetWindowHeight() const;
	HWND GetWindowHandle() const;
	bool IsWindowFullScreen() const;

};

inline CDirectGraphicsDevice& PrimaryDevice()
{
	return CDirectGraphicsDevice::GetInstance();
}