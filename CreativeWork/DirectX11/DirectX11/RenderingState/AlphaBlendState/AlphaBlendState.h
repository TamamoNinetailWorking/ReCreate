#pragma once

#include <d3d11.h>
#include <Singleton/Singleton.h>

#pragma comment(lib,"d3d11.lib")

class CAlphaBlendState : public CSingleton<CAlphaBlendState>
{
	friend class CSingleton<CAlphaBlendState>;
private:

	/* Device */
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

	/* Alpha Blend State */
	ID3D11BlendState* m_pBlendState;
	ID3D11BlendState* m_pAddBlendState;
	ID3D11BlendState* m_pAlignmentBlendState;

	bool default_blend_state(bool enable);
	bool add_blend_state(bool enable);
	bool alignment_blend_state(bool enable);


public:

	enum State
	{
		Default,
		Add,
		Alignment,

		Max,
	};

	virtual ~CAlphaBlendState() {}

	bool Init(ID3D11Device*& device, ID3D11DeviceContext*& device_context);
	void Exit();


	void SetBlendState(State state);
};

inline CAlphaBlendState& AlphaBlendState()
{
	return CAlphaBlendState::GetInstance();
}