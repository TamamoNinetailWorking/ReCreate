#pragma once

#include <Singleton/Singleton.h>
#include <d3d11.h>
#include <vector>

#pragma comment(lib,"d3d11.h")

class CViewportSetting : public CSingleton<CViewportSetting>
{
	friend class CSingleton<CViewportSetting>;
private:

	/* Device */
	ID3D11DeviceContext* m_pDeviceContext;

	/* Viewport */
	std::vector<D3D11_VIEWPORT> m_pViewPortSetting;

public:

	virtual ~CViewportSetting() {};

	bool Init(ID3D11DeviceContext*& deviceContext);
	void AddViewportSetting(UINT Number, FLOAT width, FLOAT height, FLOAT minDepth, FLOAT maxDepth, FLOAT topLeftX, FLOAT topLeftY);
	void Exit();

	void SetViewportSetting(UINT Number = 0);//Default is First Setting.
	void SetAllViewportSettings();

};

inline CViewportSetting& ViewportSetting()
{
	return CViewportSetting::GetInstance();
}