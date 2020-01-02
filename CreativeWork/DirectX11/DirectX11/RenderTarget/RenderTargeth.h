#pragma once

#include <d3d11.h>

#pragma comment(lib,"d3d11.lib")

class CRenderTarget
{
private:

	/* IsMainBuffer */
	bool m_bIsMain;

	/* Device */
	ID3D11Device* m_pDevice;
	IDXGISwapChain* m_pSwapChain;

	/* Size */
	UINT m_nWidth;
	UINT m_nHeight;

	/* RenderTarget View */
	ID3D11Texture2D* m_pTex;
	ID3D11ShaderResourceView* m_pSRV;
	ID3D11RenderTargetView* m_pRTV;

	bool general_render_target();
	bool main_render_target();


public:

	CRenderTarget();
	explicit CRenderTarget(ID3D11Device*& device,IDXGISwapChain*& swapchain);
	virtual ~CRenderTarget();

	void Init(ID3D11Device*& device,IDXGISwapChain*& swapchain);
	void Exit();

	bool CreateRenderTarget(
		bool isMain = false,
		UINT width = 1024,
		UINT height = 1024
	);

	bool CreateCubeRenderTarget(
		UINT width = 1024,
		UINT height = 1024,
		UINT size = 6
	);

};