#pragma once

#include <DirectXMath.h>
#include <D3DObject/Component/D3DDrawer.h>

class C3DDrawer : public CD3DDrawer
{
protected:

	struct ConstantBufferWorld
	{
		DirectX::XMMATRIX world;
	};

	struct Vertex
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 uv;
	};

public:



};