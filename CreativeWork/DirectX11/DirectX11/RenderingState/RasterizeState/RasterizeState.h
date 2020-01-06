#pragma once

#include <Singleton/Singleton.h>
#include <d3d11.h>
#include <vector>

#pragma comment(lib,"d3d11.lib")

class CRasterizeState : public CSingleton<CRasterizeState>
{
	friend class CSingleton<CRasterizeState>;

public:

	enum State
	{
		CullingNone,
		FrontCulling,
		BackCulling,

		CullingNone_WireFrame,
		FrontCulling_WireFrame,
		BackCulling_WireFrame,

		Max,
	};

private:

	/* Device */
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

	/* Rasterize State */
	std::vector<ID3D11RasterizerState*> m_pRasterState;

	bool raster_state(ID3D11RasterizerState*& rasterState, State state);
	bool create_rasterizer_state(ID3D11RasterizerState*& rasterizer, D3D11_CULL_MODE cull_mode,D3D11_FILL_MODE fill_mode);

public:

	virtual ~CRasterizeState() {}

	bool Init(ID3D11Device*& device, ID3D11DeviceContext*& device_context);
	void Exit();

	void SetRasterizeState(State state);
};

inline CRasterizeState& RasterizeState()
{
	return CRasterizeState::GetInstance();
}