#include "RasterizeState.h"
#include <Utility/EnderUtility.h>
#include <iostream>

using namespace std;

bool CRasterizeState::create_rasterizer_state(ID3D11RasterizerState*& rasterizer, D3D11_CULL_MODE cull_mode, D3D11_FILL_MODE fill_mode)
{
	D3D11_RASTERIZER_DESC rasterDesc;
	//setup the raster description which will determine how and what polygons will be drawn
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = cull_mode;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = fill_mode;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	//create the rasterrizer state from the description we just filled out
	HRESULT hr = m_pDevice->CreateRasterizerState(&rasterDesc, &rasterizer);
	if (FAILED(hr))
	{
		cout << "Create RasterizeState Error." << endl;
		return false;
	}
	return true;
}

bool CRasterizeState::raster_state(ID3D11RasterizerState*& rasterState,State state)
{
	switch (state)
	{
		case State::CullingNone:

			create_rasterizer_state(rasterState, D3D11_CULL_NONE, D3D11_FILL_SOLID);

			break;

		case State::FrontCulling:

			create_rasterizer_state(rasterState, D3D11_CULL_FRONT, D3D11_FILL_SOLID);

			break;

		case State::BackCulling:

			create_rasterizer_state(rasterState, D3D11_CULL_BACK, D3D11_FILL_SOLID);

			break;

		case State::CullingNone_WireFrame:

			create_rasterizer_state(rasterState, D3D11_CULL_NONE, D3D11_FILL_WIREFRAME);

			break;

		case State::FrontCulling_WireFrame:

			create_rasterizer_state(rasterState, D3D11_CULL_FRONT, D3D11_FILL_WIREFRAME);

			break;

		case State::BackCulling_WireFrame:

			create_rasterizer_state(rasterState, D3D11_CULL_BACK, D3D11_FILL_WIREFRAME);

			break;

		default:
			break;
	}
}

bool CRasterizeState::Init(ID3D11Device*& device, ID3D11DeviceContext*& device_context)
{
	m_pDevice = device;
	m_pDeviceContext = device_context;

	bool sts;
	for (BYTE state = 0; state < State::Max; state++)
	{
		ID3D11RasterizerState* rasterizeState;
		sts = raster_state(rasterizeState, static_cast<State>(state));
		if (!sts)
		{
			return false;
		}
		
		m_pRasterState.push_back(rasterizeState);
	}

	return true;
}
void CRasterizeState::Exit()
{
	ReleaseVector(m_pRasterState);
}

void CRasterizeState::SetRasterizeState(State state)
{
	m_pDeviceContext->RSSetState(m_pRasterState[static_cast<UINT>(state)]);
}