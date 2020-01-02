#include "DirectX11.h"
#include <iostream>
#include <Utility/EnderUtility.h>

#pragma comment(lib,"dxgi.lib")

using namespace std;

HRESULT CDirectGraphicsDevice::Create_Device_And_SwapChain()
{
	HRESULT hr = S_OK;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes;
	unsigned int numerator = 60;
	unsigned int denominator = 1;
	DXGI_MODE_DESC* displayModeList;

	//ドライバの種類
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	unsigned int numDriverTypes = ARRAYSIZE(driverTypes);
	unsigned int createDeviceFlags = 0;

	//機能レベル
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	// Create a DirectX graphics interface factory
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// use the factory to create an adpter for the primary graphics interface(video card)
	hr = factory->EnumAdapters(0, &adapter);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// enumerrate primary adapter output(monitor)
	hr = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// get the number of modes that fit the DXGI_FORMAT_R8G8B8_UNORM display format forthe adapter output(monitor)
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// create alist to hold all possible display modes for this monitor/video card combination
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
	{
		return E_FAIL;
	}

	// now fill the display mode list structures
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// now go through all the display modes and find the one that matches the screen width and height
	// when a match is found store the numerator and denominator of the refresh rate for that monitor
	for (unsigned int i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == m_width)
		{
			if (displayModeList[i].Height == m_height)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	delete[] displayModeList;
	displayModeList = 0;

	adapterOutput->Release();
	adapterOutput = 0;

	adapter->Release();
	adapter = 0;

	factory->Release();
	factory = 0;


	//スワップチェインの設定(ダブルバッファの管理)
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	sd.BufferCount = 1;
	sd.BufferDesc.Width = m_width;
	sd.BufferDesc.Height = m_height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = numerator;
	sd.BufferDesc.RefreshRate.Denominator = denominator;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = m_hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if (m_full_screen)
	{
		sd.Windowed = false;
	}
	else
	{
		sd.Windowed = TRUE;
	}
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_DriverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,
			m_DriverType,
			NULL,
			createDeviceFlags,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&sd,
			&m_pSwapChain,
			&m_pDevice,
			&m_FeatureLevel,
			&m_pDeviceContext);
		if (SUCCEEDED(hr))
		{
			break;
		}
	}
	if (FAILED(hr))
	{
		return E_FAIL;
	}
	else
	{
		return S_OK;
	}

}

bool CDirectGraphicsDevice::Init(HWND hwnd, bool full_screen_flag, int width, int height)
{
	m_hwnd = hwnd;
	m_width = width;
	m_height = height;
	m_full_screen = full_screen_flag;

	HRESULT hr;
	hr = Create_Device_And_SwapChain();
	if (FAILED(hr))
	{
		cout << "Device and SwapChain Create Faild." << endl;
		return false;
	}

	return true;
}

void CDirectGraphicsDevice::Exit()
{
	if (m_pDeviceContext != nullptr)
	{
		m_pDeviceContext->ClearState();
	}

	if (m_pSwapChain)
	{
		m_pSwapChain->SetFullscreenState(false, NULL);
	}

	Release(m_pDeviceContext);
	Release(m_pDevice);
	Release(m_pSwapChain);

	return;
}

ID3D11Device*& CDirectGraphicsDevice::GetDevice()
{
	return m_pDevice;
}

ID3D11DeviceContext*& CDirectGraphicsDevice::GetImmediateContext()
{
	return m_pDeviceContext;
}

IDXGISwapChain*& CDirectGraphicsDevice::GetSwapChain()
{
	return m_pSwapChain;
}

int CDirectGraphicsDevice::GetWindowWidth() const
{
	return m_width;
}

int CDirectGraphicsDevice::GetWindowHeight() const
{
	return m_height;
}

HWND CDirectGraphicsDevice::GetWindowHandle() const
{
	return m_hwnd;
}

bool CDirectGraphicsDevice::IsWindowFullScreen() const
{
	return m_full_screen;
}