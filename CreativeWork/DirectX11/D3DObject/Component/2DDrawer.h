#pragma once

#include <DirectXMath.h>
#include <D3DObject/Component/D3DDrawer.h>

class C2DDrawer : public CD3DDrawer
{
protected:

	struct ConstantBufferWorld
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX projection;
	};

	struct Vertex
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 uv;
	};


public:



};