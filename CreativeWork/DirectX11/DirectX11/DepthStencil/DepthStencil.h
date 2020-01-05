#pragma once

#include <d3d11.h>

#pragma comment(lib,"d3d11.lib")

class CDepthStencil
{
private:

	/* Device */
	ID3D11Device* m_pDevice;

	/* Size */
	UINT m_nWidth;
	UINT m_nHeight;
	UINT m_nArraySize;

	/* Depth Stencil View */
	ID3D11Texture2D* m_pTex;
	ID3D11DepthStencilView* m_pDSV;

	bool general_depth_buffer();
	bool cube_depth_buffer();

public:

	CDepthStencil();
	explicit CDepthStencil(ID3D11Device*& device);
	virtual ~CDepthStencil();

	void Init(ID3D11Device*& device);
	void Exit();

	bool CreateDepthStencil(
		UINT width = 1024,
		UINT height = 1024
	);

	bool CreateCubeDepthStencil(
		UINT width = 1024,
		UINT height = 1024,
		UINT size = 6
	);

	ID3D11Texture2D*& GetTexture();
	ID3D11DepthStencilView*& GetDepthStencilView();

};