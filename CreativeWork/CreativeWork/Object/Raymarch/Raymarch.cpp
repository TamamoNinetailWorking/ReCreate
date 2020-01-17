#include "Raymarch.h"
#include <iostream>
#include "../../Component/RaymarchComponent/RaymarchComponent.h"

void CRaymarch::init_component()
{
	AddComponent<CRaymarchComponent>();
}

void CRaymarch::Start()
{
	CObject::Start();
	
	init_component();
}

void CRaymarch::Update()
{
	//std::cout << "Raymarch Update." << std::endl;

	CObject::Update();
}