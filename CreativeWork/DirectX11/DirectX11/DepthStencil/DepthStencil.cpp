#include "DepthStencil.h"
#include <Utility/EnderUtility.h>
#include <iostream>

using namespace std;

CDepthStencil::CDepthStencil()
{
	m_pDevice = nullptr;
}

explicit CDepthStencil::CDepthStencil(ID3D11Device*& device)
{
	Init(device);
}

CDepthStencil::~CDepthStencil()
{
	Exit();
}

void CDepthStencil::Init(ID3D11Device*& device)
{
	m_pDevice = device;
}

void CDepthStencil::Exit()
{
	Release(m_pDSV);
	Release(m_pTex);
}

bool CDepthStencil::general_depth_buffer()
{
	//Create Depth Buffer
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	depthBufferDesc.Width = m_nWidth;
	depthBufferDesc.Height = m_nHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = m_nArraySize;
	depthBufferDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	HRESULT hr = m_pDevice->CreateTexture2D(&depthBufferDesc, NULL, &m_pTex);
	if (FAILED(hr))
	{
		cout << "Create Depth Stencil Buffer Error." << endl;
		return false;
	}

	//Create Depth Stencil View
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = depthBufferDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	//create the depth stencil view
	hr = m_pDevice->CreateDepthStencilView(m_pTex, &depthStencilViewDesc, &m_pDSV);
	if (FAILED(hr))
	{
		cout << "Create Depth Stencil View Error." << endl;
		return false;
	}

	return true;
}

bool CDepthStencil::cube_depth_buffer()
{
	HRESULT hr;

	//Create Cube Depth Buffer
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = m_nWidth;
	descDepth.Height = m_nHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = m_nArraySize;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

	hr = m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pTex);
	if (FAILED(hr))
	{
		cout << "Create Cube Depth Stencil Buffer Error." << endl;
		return false;
	}

	//Create Cube DepthStencil View
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
	descDSV.Texture2DArray.FirstArraySlice = 0;
	descDSV.Texture2DArray.ArraySize = m_nArraySize;
	descDSV.Texture2DArray.MipSlice = 0;
	descDSV.Flags = D3D11_RESOURCE_MISC_TEXTURECUBE;

	hr = m_pDevice->CreateDepthStencilView(m_pTex, NULL, &m_pDSV);
	if (FAILED(hr))
	{
		cout << "Create Cube Depth Stencil View Error." << endl;
		return false;
	}

	return true;
}

bool CDepthStencil::CreateDepthStencil(UINT width, UINT height)
{
	m_nWidth = width;
	m_nHeight = height;
	m_nArraySize = 1;

	return general_depth_buffer();
}

bool CDepthStencil::CreateCubeDepthStencil(UINT width, UINT height, UINT size)
{
	m_nWidth = width;
	m_nHeight = height;
	m_nArraySize = size;

	return cube_depth_buffer();
}

ID3D11Texture2D*& CDepthStencil::GetTexture()
{
	return m_pTex;
}

ID3D11DepthStencilView*& CDepthStencil::GetDepthStencilView()
{
	return m_pDSV;
}