#include "DepthStencilState.h"
#include <iostream>
#include <Utility/EnderUtility.h>

using namespace std;


bool CDepthStencilState::general_depth_stencil()
{
	HRESULT hr;

	//Create Stencil State
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	//set up the description of the stencil state
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	//stencil operation if pixel is front-facing
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//stencil opeartion if pixel is back-facing
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//create the depth stencil state
	hr = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStencilGeneral);
	if (FAILED(hr))
	{
		cout << "Create General DepthStencil Error." << endl;
		return false;
	}

	return true;
}

bool CDepthStencilState::none_depth_stencil()
{
	HRESULT hr;

	//Create Depth Stencil
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = false;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	//set up the description of the stencil state
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	//stencil operation if pixel is front-facing
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//stencil opeartion if pixel is back-facing
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//create the depth stencil state
	 hr = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStencilNone);
	if (FAILED(hr))
	{
		cout << "Create None Depth Stencil State Error." << endl;
		return false;
	}

	return true;
}

bool CDepthStencilState::Init(ID3D11Device*& device,ID3D11DeviceContext*& immediateContext)
{
	m_pDevice = device;
	m_pImmediateContext = immediateContext;

	bool result = false;
	
	result = general_depth_stencil();
	if (!result)
	{
		return false;
	}

	result = none_depth_stencil();
	if (!result)
	{
		return false;
	}

	cout << "Successed Create Depth Stencil State!!" << endl;
	return true;
}

void CDepthStencilState::Exit()
{
	Release(m_pDepthStencilGeneral);
	Release(m_pDepthStencilNone);

	m_pImmediateContext = nullptr;
	m_pDevice = nullptr;

	return;
}

void CDepthStencilState::SetStencilState(CDepthStencilState::State state)
{
	switch (state)
	{
		case State::Max://Error
		case State::Default:

			m_pImmediateContext->OMSetDepthStencilState(m_pDepthStencilGeneral, 1);

			break;

		case State::None:

			m_pImmediateContext->OMSetDepthStencilState(m_pDepthStencilNone, 1);

			break;
	}
}