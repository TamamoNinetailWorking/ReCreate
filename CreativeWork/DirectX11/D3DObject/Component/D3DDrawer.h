#pragma once

#include <d3d11.h>
#include <Object/DrawComponent/DrawComponent.h>
#include <Utility/EnderUtility.h>
#include <Shader/ShaderSet.h>

class CD3DDrawer 
	: public CDrawer<ID3D11Buffer,ID3D11Buffer,ID3D11Buffer,ID3D11Buffer,ID3D11Buffer,ID3D11ShaderResourceView>
{
protected:

	/* Device */
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

	/* SamplerState */
	ID3D11SamplerState* m_pSamplerState;

	/* ShaderSet */
	CShaderSet* m_pShader;

	virtual bool shader_init() {};
	virtual bool constant_buffer_init() {};
	virtual bool sampler_init() {};

	virtual bool construction_init();

public:

	virtual bool Init(ID3D11Device*& dev, ID3D11DeviceContext*& devCon);

};