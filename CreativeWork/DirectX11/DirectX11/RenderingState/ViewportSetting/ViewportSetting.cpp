#include "ViewportSetting.h"
#include <Utility/EnderUtility.h>
#include <iostream>

using namespace std;

bool CViewportSetting::Init(ID3D11DeviceContext*& deviceContext)
{
	m_pDeviceContext = deviceContext;
	return true;
}

void CViewportSetting::AddViewportSetting(UINT Number, FLOAT width, FLOAT height, FLOAT minDepth, FLOAT maxDepth, FLOAT topLeftX, FLOAT topLeftY)
{
	if (m_pViewPortSetting.size() <= Number)
	{
		//Out of Range New Comer
		D3D11_VIEWPORT vp;
		vp.Width = width;
		vp.Height = height;
		vp.MinDepth = minDepth;
		vp.MaxDepth = maxDepth;
		vp.TopLeftX = topLeftX;
		vp.TopLeftY = topLeftY;

		m_pViewPortSetting.push_back(vp);
	}
	else
	{
		//OverRide
		m_pViewPortSetting[Number].Width = width;
		m_pViewPortSetting[Number].Height = height;
		m_pViewPortSetting[Number].MinDepth = minDepth;
		m_pViewPortSetting[Number].MaxDepth = maxDepth;
		m_pViewPortSetting[Number].TopLeftX = topLeftX;
		m_pViewPortSetting[Number].TopLeftY = topLeftY;
	}

	return;
}


void CViewportSetting::Exit()
{
	m_pViewPortSetting.clear();
}

void CViewportSetting::SetViewportSetting(UINT Number)
{
	m_pDeviceContext->RSSetViewports(1, &m_pViewPortSetting[Number]);
}

void CViewportSetting::SetAllViewportSettings()
{
	UINT num = m_pViewPortSetting.size();
	D3D11_VIEWPORT* vp = new D3D11_VIEWPORT[num];

	for (UINT i = 0; i < num; i++)
	{
		vp[i] = m_pViewPortSetting[i];
	}

	m_pDeviceContext->RSSetViewports(num, vp);

	delete[] vp;

	return;
}
