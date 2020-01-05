#include "RenderTargeth.h"
#include <Utility/EnderUtility.h>
#include <iostream>

using namespace std;

CRenderTarget::CRenderTarget()
{
	m_bIsMain = false;
	m_pDevice = nullptr;
	m_pSwapChain = nullptr;
}

CRenderTarget::CRenderTarget(ID3D11Device*& device,IDXGISwapChain*& swapchain)
{
	m_bIsMain = false;
	Init(device,swapchain);
}

CRenderTarget::~CRenderTarget()
{
	Exit();
}

void CRenderTarget::Init(ID3D11Device*& device,IDXGISwapChain*& swapchain)
{
	m_pDevice = device;
	m_pSwapChain = swapchain;
}

void CRenderTarget::Exit()
{
	Release(m_pRTV);
	Release(m_pSRV);
	Release(m_pTex);
}

bool CRenderTarget::general_render_target()
{
	HRESULT hr;

	D3D11_TEXTURE2D_DESC Tex2DDesc;
	D3D11_RENDER_TARGET_VIEW_DESC RTVDesc;

	::ZeroMemory(&Tex2DDesc, sizeof(D3D11_TEXTURE2D_DESC));
	Tex2DDesc.ArraySize = 1;
	Tex2DDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	Tex2DDesc.Usage = D3D11_USAGE_DEFAULT;
	Tex2DDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	Tex2DDesc.Width = m_nWidth;
	Tex2DDesc.Height = m_nHeight;
	Tex2DDesc.MipLevels = 1;
	Tex2DDesc.SampleDesc.Count = 1;

	hr = m_pDevice->CreateTexture2D(&Tex2DDesc, NULL, &m_pTex);
	if (FAILED(hr))
	{
		cout << "Create Texture 2D Error." << endl;
		return false;
	}

	::ZeroMemory(&RTVDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	RTVDesc.Format = Tex2DDesc.Format;
	RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	RTVDesc.Texture2D.MipSlice = 0;

	hr = m_pDevice->CreateRenderTargetView(m_pTex, &RTVDesc, &m_pRTV);
	if (FAILED(hr))
	{
		cout << "CreateRenderTargetView Error." << endl;
		return false;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	::ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.Format = RTVDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	hr = m_pDevice->CreateShaderResourceView(m_pTex, &srvDesc, &m_pSRV);
	if (FAILED(hr))
	{
		cout << "CreateRenderTargetShaderResource Error." << endl;
		return false;
	}

	return true;
}

bool CRenderTarget::main_render_target()
{
	HRESULT hr;

	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pTex);

	if (FAILED(hr))
	{
		cout << "Create Texture 2D Error.(main_render_target)" << endl;
		return false;
	}

	hr = m_pDevice->CreateRenderTargetView(m_pTex, NULL, &m_pRTV);

	if (FAILED(hr))
	{
		cout << "CreateRenderTargetView Error.(main_render_target)" << endl;
		return false;
	}

	return true;
}

bool CRenderTarget::cube_render_target()
{
	HRESULT hr;

	//Create Texture
	D3D11_TEXTURE2D_DESC Desc;
	ZeroMemory(&Desc, sizeof(Desc));
	Desc.ArraySize = m_nArraySize;
	Desc.Width = m_nWidth;
	Desc.Height = m_nHeight;
	Desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.CPUAccessFlags = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	Desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS | D3D11_RESOURCE_MISC_TEXTURECUBE;
	Desc.MipLevels = 1;

	hr = m_pDevice->CreateTexture2D(&Desc, NULL, &m_pTex);
	if (FAILED(hr))
	{
		cout << "Create Cube Texture 2D Error." << endl;
		return false;
	}

	//Create Cube Shader Resource View
	D3D11_SHADER_RESOURCE_VIEW_DESC descSRV;
	ZeroMemory(&descSRV, sizeof(descSRV));
	descSRV.Format = Desc.Format;
	descSRV.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	descSRV.TextureCube.MipLevels = Desc.MipLevels;
	descSRV.TextureCube.MostDetailedMip = 0;

	hr = m_pDevice->CreateShaderResourceView(m_pTex, &descSRV, &m_pSRV);
	if (FAILED(hr))
	{
		cout << "Create Cube RenderTargetView Error." << endl;
		return false;
	}

	//Create Cube Render Target View 
	D3D11_RENDER_TARGET_VIEW_DESC renderDesc;
	renderDesc.Format = Desc.Format;
	renderDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
	renderDesc.Texture2DArray.ArraySize = m_nArraySize;
	renderDesc.Texture2DArray.FirstArraySlice = 0;
	renderDesc.Texture2DArray.MipSlice = 0;

	hr = m_pDevice->CreateRenderTargetView(m_pTex, &renderDesc, &m_pRTV);
	if (FAILED(hr))
	{
		cout << "Create Cube RenderTargetShaderResource Error." << endl;
		return false;
	}

	return true;
}

bool CRenderTarget::CreateRenderTarget(bool isMain, UINT width, UINT height)
{
	m_nArraySize = 1;

	if (isMain)
	{
		return main_render_target();
	}
	else
	{
		m_nWidth = width;
		m_nHeight = height;

		return general_render_target();
	}
}

bool CRenderTarget::CreateCubeRenderTarget(UINT width, UINT height, UINT size)
{
	m_nWidth = width;
	m_nHeight = height;
	m_nArraySize = size;

	return cube_render_target();
}

ID3D11Texture2D*& CRenderTarget::GetTexture()
{
	return m_pTex;
}

ID3D11ShaderResourceView*& CRenderTarget::GetShaderResourceView()
{
	return m_pSRV;
}

ID3D11RenderTargetView*& CRenderTarget::GetRenderTargetView()
{
	return m_pRTV;
}