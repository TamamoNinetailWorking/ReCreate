#pragma once

#include <d3d11.h>
#include <Object/DrawComponent/DrawComponent.h>
#include <Utility/EnderUtility.h>

class CD3DDrawer 
	: public CDrawer<ID3D11Buffer,ID3D11Buffer,ID3D11Buffer,ID3D11Buffer,ID3D11Buffer,ID3D11ShaderResourceView>
{
protected:

	ID3D11SamplerState* m_pSamplerState;

};