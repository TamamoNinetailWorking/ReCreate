#include "AlphaBlendState.h"
#include <Utility/EnderUtility.h>
#include <iostream>

using namespace std;

bool CAlphaBlendState::default_blend_state(bool enable)
{
	D3D11_RENDER_TARGET_BLEND_DESC renderTarget;
	renderTarget.BlendEnable = FALSE;
	renderTarget.SrcBlend = D3D11_BLEND_ONE;
	renderTarget.DestBlend = D3D11_BLEND_ZERO;
	renderTarget.BlendOp = D3D11_BLEND_OP_ADD;
	renderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
	renderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
	renderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	renderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = enable;// TRUEの場合、マルチレンダーターゲットで各レンダーターゲットのブレンドステートの設定を個別に設定できる// FALSEの場合、0番目のみが使用される

	BlendDesc.IndependentBlendEnable = true;

	memcpy_s((void*)&BlendDesc.RenderTarget[0], sizeof(BlendDesc.RenderTarget[0]), (void*)&renderTarget, sizeof(renderTarget));

	if (FAILED(m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState)))
	{
		cout << "Create Default Blend State Error." << endl;
		return false;
	}
	return true;
}

bool CAlphaBlendState::add_blend_state(bool enable)
{
	D3D11_RENDER_TARGET_BLEND_DESC renderTarget;
	renderTarget.BlendEnable = TRUE;
	renderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	renderTarget.DestBlend = D3D11_BLEND_ONE;
	renderTarget.BlendOp = D3D11_BLEND_OP_ADD;
	renderTarget.SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	renderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
	renderTarget.BlendOpAlpha = D3D11_BLEND_OP_MAX;
	renderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = enable;// TRUEの場合、マルチレンダーターゲットで各レンダーターゲットのブレンドステートの設定を個別に設定できる// FALSEの場合、0番目のみが使用される

	BlendDesc.IndependentBlendEnable = true;

	memcpy_s((void*)&BlendDesc.RenderTarget[0], sizeof(BlendDesc.RenderTarget[0]), (void*)&renderTarget, sizeof(renderTarget));

	if (FAILED(m_pDevice->CreateBlendState(&BlendDesc, &m_pAddBlendState)))
	{
		cout << "Create Add Blend State Error." << endl;
		return false;
	}
	return true;
}

bool CAlphaBlendState::alignment_blend_state(bool enable)
{
	D3D11_RENDER_TARGET_BLEND_DESC renderTarget;
	renderTarget.BlendEnable = TRUE;
	renderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	renderTarget.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	renderTarget.BlendOp = D3D11_BLEND_OP_ADD;
	renderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
	renderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
	renderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	renderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = enable;// TRUEの場合、マルチレンダーターゲットで各レンダーターゲットのブレンドステートの設定を個別に設定できる// FALSEの場合、0番目のみが使用される

	BlendDesc.IndependentBlendEnable = false;

	memcpy_s((void*)&BlendDesc.RenderTarget[0], sizeof(BlendDesc.RenderTarget[0]), (void*)&renderTarget, sizeof(renderTarget));

	if (FAILED(m_pDevice->CreateBlendState(&BlendDesc, &m_pAlignmentBlendState)))
	{
		cout << "Create Alignment Blend State Error." << endl;
		return false;
	}
	return true;
}

bool CAlphaBlendState::Init(ID3D11Device*& device, ID3D11DeviceContext*& device_context)
{
	m_pDevice = device;
	m_pDeviceContext = device_context;

	bool result;

	result = default_blend_state(false);
	if (!result)
	{
		return false;
	}

	result = add_blend_state(false);
	if (!result)
	{
		return false;
	}

	result = alignment_blend_state(false);
	if (!result)
	{
		return false;
	}

	return true;
}

void CAlphaBlendState::Exit()
{
	Release(m_pAlignmentBlendState);
	Release(m_pAddBlendState);
	Release(m_pBlendState);
}

void CAlphaBlendState::SetBlendState(State state)
{
	UINT mask = 0xffffffff;

	switch (state)
	{
		case State::Default:
		case State::Max:

			m_pDeviceContext->OMSetBlendState(m_pBlendState, NULL, mask);

			break;

		case State::Add:

			m_pDeviceContext->OMSetBlendState(m_pAddBlendState, NULL, mask);

			break;

		case State::Alignment:

			m_pDeviceContext->OMSetBlendState(m_pAlignmentBlendState, NULL, mask);

			break;
	}
}