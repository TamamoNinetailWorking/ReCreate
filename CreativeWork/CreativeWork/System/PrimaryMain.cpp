#include <iostream>
#include <DirectX11/SystemWrapper/SystemWrapper.h>
#include <DirectXCollision.h>

using namespace std;

void PrimaryMain()
{
	GraphicsSystem().ClearForColor(0, 0, 0);

	GraphicsSystem().Present();

	return;
}