#include "D3DDrawer.h"
#include <iostream>

using namespace std;

bool CD3DDrawer::construction_init()
{
	if (!shader_init())
	{
		cout << "shader init failed." << endl;
		return false;
	}

	if (!constant_buffer_init())
	{
		cout << "constant buffer init failed." << endl;
		return false;
	}

	if (!sampler_init())
	{
		cout << "sampler init failed." << endl;
		return false;
	}

	return true;
}

bool CD3DDrawer::Init(ID3D11Device*& dev, ID3D11DeviceContext*& devCon)
{
	m_pDevice = dev;
	m_pDeviceContext = devCon;

	if (!construction_init())
	{
		cout << "construction init failed." << endl;
		return false;
	}
	
	return true;
}