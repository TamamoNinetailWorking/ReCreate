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
	ID3D11DeviceContext*& m_pDeviceContext;

	/* ShaderSet */
	NShaderManager::VertexShaderMap m_pVertexShaderMap;
	NShaderManager::InputLayoutMap m_pInputLayoutMap;
	NShaderManager::PixelShaderMap m_pPixelShaderMap;
	NShaderManager::GeometryShaderMap m_pGeometryShaderMap;
	NShaderManager::HullShaderMap m_pHullShaderMap;
	NShaderManager::DomainShaderMap m_pDomainShaderMap;
	NShaderManager::ComputeShaderMap m_pComputeShaderMap;

	void AllClear();

public:

	virtual ~CShaderManager();

	void Init(ID3D11Device*& device, ID3D11DeviceContext*& device_context);

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
		ID3D11InputLayout*& pInputLayout);

	bool GetPixelShader(
		const char* file_name,
		const char* func_name,
		ID3D11PixelShader*& pPixelShader);

	bool GetGeometryShader(
		const char* file_name,
		const char* func_name,
		ID3D11GeometryShader*& pGeometryShader);

	bool GetHullShader(
		const char* file_name,
		const char* func_name,
		ID3D11HullShader*& pHullShader);

	bool GetDomainShader(
		const char* file_name,
		const char* func_name,
		ID3D11DomainShader*& pDomainShader);

	bool GetComputeShader(
		const char* file_name,
		const char* func_name,
		ID3D11ComputeShader*& pComputeShader);

};

inline CShaderManager& ShaderManager()
{
	return CShaderManager::GetInstance();
}