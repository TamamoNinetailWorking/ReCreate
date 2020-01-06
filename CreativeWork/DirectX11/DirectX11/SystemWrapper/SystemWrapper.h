#pragma once

#include <Singleton/Singleton.h>
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")

class CRenderTarget;
class CDepthStencil;

class CGraphicsSystem : public CSingleton<CGraphicsSystem>
{
	friend class CSingleton<CGraphicsSystem>;
private:

	/* Window Config */
	HWND m_hwnd;
	int m_width, m_height;
	bool m_full_screen;

	/* Rendering Target */
	CRenderTarget* m_pRenderTarget;
	CDepthStencil* m_pDepthStencil;

	bool render_target_setting();
	bool depth_stencil_setting();

	void exit_render_target();
	void exit_depth_stencil();

public:

	virtual ~CGraphicsSystem() {}

	bool Init(HWND hwnd, int width, int height, bool full_screen);
	void Exit();

	void SetDefaultRenderTarget();
	void SetRenderTarget(ID3D11RenderTargetView*& rtv, ID3D11DepthStencilView*& dsv);

};

inline CGraphicsSystem& GraphicsSystem()
{
	return CGraphicsSystem::GetInstance();
}