#include <iostream>
#include <DirectX11/SystemWrapper/SystemWrapper.h>
#include <Object/ObjectManager/ObjectManager.h>
#include "../Object/Raymarch/Raymarch.h"

using namespace std;

void PrimaryInit()
{
	CRaymarch* m_pRaymarch = new CRaymarch();
}

void PrimaryMain()
{

	static bool init_flag = false;

	if (!init_flag)
	{
		PrimaryInit();
		init_flag = true;
	}

	ObjectManager().Update();
	ObjectManager().DrawUpdate();

	GraphicsSystem().ClearForColor(0, 0, 0);
	ObjectManager().Draw();
	GraphicsSystem().Present();

	return;
}