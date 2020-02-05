#pragma once

#include <map>
#include <Singleton/Singleton.h>

#include "ShaderManagementSpace.h"

class CShaderManager : public CSingleton<CShaderManager>
{
	friend class CSingleton<CShaderManager>;
private:

	/* Device */
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

	/* ShaderSet */
	//Vertex
	NShaderManager::VertexShaderMap m_pVertexShaderMap;
	NShaderManager::ClassLinkageMap m_pVertexLinkMap;
	NShaderManager::InputLayoutMap m_pInputLayoutMap;
	//Pixel
	NShaderManager::PixelShaderMap m_pPixelShaderMap;
	NShaderManager::ClassLinkageMap m_pPixelLinkMap;
	//Geometry
	NShaderManager::GeometryShaderMap m_pGeometryShaderMap;
	NShaderManager::ClassLinkageMap m_pGeometryLinkMap;
	//Hull
	NShaderManager::HullShaderMap m_pHullShaderMap;
	NShaderManager::ClassLinkageMap m_pHullLinkMap;
	//Domain
	NShaderManager::DomainShaderMap m_pDomainShaderMap;
	NShaderManager::ClassLinkageMap m_pDomainLinkMap;
	//Compute
	NShaderManager::ComputeShaderMap m_pComputeShaderMap;
	NShaderManager::ClassLinkageMap m_pComputeLinkMap;

	void AllClear();

public:

	virtual ~CShaderManager() {};

	void Init(ID3D11Device*& device, ID3D11DeviceContext*& device_context);
	void Exit();

	bool CheckWhetherVertexShaderIsAbleToChatch(
		const char* file_name,
		const char* func_name);

	bool CheckWhetherInputLayoutIsAbleToChatch(
		const char* file_name,
		const char* func_name);

	bool CheckWhetherPixelShaderIsAbleToChatch(
		const char* file_name,
		const char* func_name);

	bool CheckWhetherGeometryShaderIsAbleToChatch(
		const char* file_name,
		const char* func_name);

	bool CheckWhetherHullShaderIsAbleToChatch(
		const char* file_name,
		const char* func_name);

	bool CheckWhetherDomainShaderIsAbleToChatch(
		const char* file_name,
		const char* func_name);

	bool CheckWhetherComputeShaderIsAbleToChatch(
		const char* file_name,
		const char* func_name);

	bool GetVertexShader(
		const char* file_name,
		const char* func_name,
		ID3D11VertexShader*& pVertexShader,
		ID3D11InputLayout*& pInputLayout,
		ID3D11ClassLinkage*& pClassLinkage,
		bool use_class);

	bool GetPixelShader(
		const char* file_name,
		const char* func_name,
		ID3D11PixelShader*& pPixelShader,
		ID3D11ClassLinkage*& pClassLinkage,
		bool use_class);

	bool GetGeometryShader(
		const char* file_name,
		const char* func_name,
		ID3D11GeometryShader*& pGeometryShader,
		ID3D11ClassLinkage*& pClassLinkage,
		bool use_class);

	bool GetHullShader(
		const char* file_name,
		const char* func_name,
		ID3D11HullShader*& pHullShader,
		ID3D11ClassLinkage*& pClassLinkage,
		bool use_class);

	bool GetDomainShader(
		const char* file_name,
		const char* func_name,
		ID3D11DomainShader*& pDomainShader,
		ID3D11ClassLinkage*& pClassLinkage,
		bool use_class);

	bool GetComputeShader(
		const char* file_name,
		const char* func_name,
		ID3D11ComputeShader*& pComputeShader,
		ID3D11ClassLinkage*& pClassLinkage,
		bool use_class);

};

inline CShaderManager& ShaderManager()
{
	return CShaderManager::GetInstance();
}