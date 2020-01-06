#include "SystemWrapper.h"
#include <Utility/EnderUtility.h>
#include <iostream>

#include <DirectX11/PrimaryDevice/DirectX11.h>
#include <DirectX11/RenderingState/AlphaBlendState/AlphaBlendState.h>
#include <DirectX11/RenderingState/DepthStencilState/DepthStencilState.h>
#include <DirectX11/RenderingState/RasterizeState/RasterizeState.h>
#include <DirectX11/RenderingState/ViewportSetting/ViewportSetting.h>

#include <DirectX11/RenderTarget/RenderTargeth.h>
#include <DirectX11/DepthStencil/DepthStencil.h>

using namespace std;

bool CGraphicsSystem::render_target_setting()
{
	m_pRenderTarget = new CRenderTarget();

	m_pRenderTarget->Init(
		PrimaryDevice().GetDevice(), 
		PrimaryDevice().GetSwapChain());

	bool result;
	result = m_pRenderTarget->CreateRenderTarget(true, m_width, m_height);
	if (!result)
	{
		return false;
	}

	return true;
}

bool CGraphicsSystem::depth_stencil_setting()
{
	m_pDepthStencil = new CDepthStencil();

	m_pDepthStencil->Init(PrimaryDevice().GetDevice());

	bool result;
	result = m_pDepthStencil->CreateDepthStencil(m_width, m_height);
	if (!result)
	{
		return false;
	}

	return true;
}

void CGraphicsSystem::exit_render_target()
{
	m_pRenderTarget->Exit();
	Delete(m_pRenderTarget);
}

void CGraphicsSystem::exit_depth_stencil()
{
	m_pDepthStencil->Exit();
	Delete(m_pDepthStencil);
}

bool CGraphicsSystem::Init(HWND hwnd, int width, int height, bool full_screen)
{
	m_hwnd = hwnd;
	m_width = width;
	m_height = height;
	m_full_screen = full_screen;

	bool result;

	/* Primary Device Init */
	result = PrimaryDevice().Init(
		m_hwnd, 
		full_screen, 
		m_width, 
		m_height);
	if (!result)
	{
		cout << "Primary Device Create Failed." << endl;
		return false;
	}

	/* Render Target Init */
	result = render_target_setting();
	if (!result)
	{
		cout << "Render Target Setting Failed." << endl;
		return false;
	}

	/* Depth Stencil Init */
	result = depth_stencil_setting();
	if (!result)
	{
		cout << "Depth Stencil Failed." << endl;
		return false;
	}

	/* Depth Stencil State Init */
	result = DepthStencilState().Init(
		PrimaryDevice().GetDevice(),
		PrimaryDevice().GetImmediateContext());
	if (!result)
	{
		cout << "Depth Stencil State Failed." << endl;
		return false;
	}

	/* Rasterize State Init */
	result = RasterizeState().Init(
		PrimaryDevice().GetDevice(),
		PrimaryDevice().GetImmediateContext());
	if (!result)
	{
		cout << "Rasterize State Failed." << endl;
		return false;
	}

	/* Viewport Init */
	result = ViewportSetting().Init(PrimaryDevice().GetImmediateContext());
	if (!result)
	{
		cout << "Viewport Settings Error. DeviceContext is null?" << endl;
		return false;
	}

	ViewportSetting().AddViewportSetting(
		0,
		static_cast<FLOAT>(m_width),
		static_cast<FLOAT>(m_height),
		0.0f,
		1.0f,
		0,
		0);
	
	/* AlphaBlend State Init */
	result = AlphaBlendState().Init(
		PrimaryDevice().GetDevice(),
		PrimaryDevice().GetImmediateContext());
	if (!result)
	{
		cout << "Alpha Blend State Failed." << endl;
		return false;
	}
	
	AlphaBlendState().SetBlendState(CAlphaBlendState::Default);

	ViewportSetting().SetViewportSetting();

	RasterizeState().SetRasterizeState(CRasterizeState::CullingNone);

	DepthStencilState().SetStencilState(CDepthStencilState::Default);
	
	SetDefaultRenderTarget();

	return true;
}

void CGraphicsSystem::Exit()
{
	AlphaBlendState().Exit();
	ViewportSetting().Exit();
	RasterizeState().Exit();
	DepthStencilState().Exit();

	exit_depth_stencil();
	exit_render_target();

	PrimaryDevice().Exit();
}

void CGraphicsSystem::SetDefaultRenderTarget()
{
	SetRenderTarget(
		m_pRenderTarget->GetRenderTargetView(),
		m_pDepthStencil->GetDepthStencilView()
	);
}

void CGraphicsSystem::SetRenderTarget(ID3D11RenderTargetView*& rtv, ID3D11DepthStencilView*& dsv)
{
	PrimaryDevice().GetImmediateContext()->OMSetRenderTargets(1,&rtv, dsv);
}

void CGraphicsSystem::ClearRenderTarget(ID3D11RenderTargetView*& render_target, const FLOAT* color)
{
	PrimaryDevice().GetImmediateContext()->ClearRenderTargetView(
		render_target,
		color);
}

void CGraphicsSystem::ClearDepthStencil(ID3D11DepthStencilView*& depth_stencil)
{
	PrimaryDevice().GetImmediateContext()->ClearDepthStencilView(
		depth_stencil, 
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 
		1.0f, 0);
}

void CGraphicsSystem::ClearForColor(FLOAT r, FLOAT g, FLOAT b)
{
	float color[4] = { r,g,b,1 };
	//カラーバッファクリア
	ClearRenderTarget(
		m_pRenderTarget->GetRenderTargetView(),
		color);

	//デプスステンシルバッファクリア
	ClearDepthStencil(m_pDepthStencil->GetDepthStencilView());

	return;
}

void CGraphicsSystem::ClearBuffer()
{
	ClearForColor(1,1,1);
}

void CGraphicsSystem::Present()
{
	PrimaryDevice().GetSwapChain()->Present(0, 0);
}