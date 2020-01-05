#pragma once

#include <Singleton/Singleton.h>
#include <d3d11.h>

#pragma comment(lib,"d3d11.lib")

class CDepthStencilState : public CSingleton<CDepthStencilState>
{
	friend class CSingleton<CDepthStencilState>;
	

private:

	/* Device */
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pImmediateContext;

	/* Depth Stencil State */
	ID3D11DepthStencilState* m_pDepthStencilGeneral;
	ID3D11DepthStencilState* m_pDepthStencilNone;

	bool general_depth_stencil();
	bool none_depth_stencil();

public:

	enum State
	{
		Default,
		None,

		Max,
	};

	virtual ~CDepthStencilState() {}

	bool Init(ID3D11Device*& device,ID3D11DeviceContext*& immediateContext);
	void Exit();

	void SetStencilState(State state);

};

inline CDepthStencilState& DepthStencilState()
{
	return CDepthStencilState::GetInstance();
}