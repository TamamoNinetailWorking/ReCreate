#include <iostream>

#include <DirectX11/SystemWrapper/SystemWrapper.h>
#include <DirectX11/PrimaryDevice/DirectX11.h>
#include <DirectX11/RenderingState/AlphaBlendState/AlphaBlendState.h>

#include <Object/ObjectManager/ObjectManager.h>

#include <Shader/ShaderSet.h>

#include <BaseSystem/Directory/DirectoryManager.h>

#include <DirectXMath.h>

using namespace std;
using namespace DirectX;

CShaderSet* m_pShaderSet = nullptr;
ID3D11ClassLinkage* g_pPSClassLinkage = nullptr;
ID3D11ClassInstance* m_pClassInstance;

struct CBUFFER0
{
	//HalfLambert
	XMFLOAT4 vecLight0;
	//Phon
	XMFLOAT4 vecLight1;
	XMFLOAT4 EyePos;
	//CelShading
	XMFLOAT4 vecLight2;
};

struct CBUFFER1
{
	XMMATRIX matWVP;
};


//Vertex Layout
struct SimpleVertex
{
	XMFLOAT3 pos;
	XMFLOAT3 normal;
	XMFLOAT2 texel;
};

void TestInit()
{
	m_pShaderSet = new CShaderSet();
	m_pShaderSet->Init(PrimaryDevice().GetImmediateContext());

	PrimaryDevice().GetDevice()->CreateClassLinkage(&g_pPSClassLinkage);

	SimpleVertex vertices[] =
	{
		XMFLOAT3(-0.5f,0.5f,0.0f),XMFLOAT3(0,0,-1),XMFLOAT2(0,0),
		XMFLOAT3(0.5f,0.5f,0.0f),XMFLOAT3(0,0,-1),XMFLOAT2(1,0),
		XMFLOAT3(-0.5f,-0.5f,0.0f),XMFLOAT3(0,0,-1),XMFLOAT2(0,1),
		XMFLOAT3(0.5f,-0.5f,0.0f),XMFLOAT3(0,0,-1),XMFLOAT2(1,1),
	};
	
}

void TestUpdate()
{

}

void TestDraw()
{
	GraphicsSystem().ClearForColor(0, 0, 0);

	AlphaBlendState().SetBlendState(CAlphaBlendState::Default);


	GraphicsSystem().Present();
}

void TestMain()
{
	static bool check = false;
	if (!check)
	{
		TestInit();
		check = true;
	}

	TestUpdate();
	TestDraw();

}