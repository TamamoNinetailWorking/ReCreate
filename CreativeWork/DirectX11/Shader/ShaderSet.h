#pragma once

#include <d3d11.h>
#include <vector>

class CShaderSet
{
private:

	/* Device */
	ID3D11DeviceContext* m_pDeviceContext;

	//VertexShaderSet
	std::vector<ID3D11VertexShader*> m_vVertexShader;
	//InputLayoutSet
	std::vector<ID3D11InputLayout*> m_vInputLayout;
	//PixelShaderSet
	std::vector<ID3D11PixelShader*> m_vPixelShader;
	//GeometryShaderSet
	std::vector<ID3D11GeometryShader*> m_vGeometryShader;
	//HullShaderSet
	std::vector<ID3D11HullShader*> m_vHullShader;
	//DomainShaderSet
	std::vector<ID3D11DomainShader*> m_vDomainShader;


public:

	//Creator
	bool CreateVertexShader(
		const char* file_name,
		const char* func_name);

	bool CreatePixelShader(
		const char* file_name,
		const char* func_name);

	bool CreateGeometryShader(
		const char* file_name,
		const char* func_name);

	bool CreateHullShader(
		const char* file_name,
		const char* func_name);

	bool CreateDomainShader(
		const char* file_name,
		const char* func_name);

	//Accessor
	ID3D11VertexShader* GetVertexShader(UINT index);
	ID3D11InputLayout* GetInputLayout(UINT index);
	ID3D11PixelShader* GetPixelShader(UINT index);
	ID3D11GeometryShader* GetGeometryShader(UINT index);
	ID3D11HullShader* GetHullShader(UINT index);
	ID3D11DomainShader* GetDomainShader(UINT index);

	void SetVertexShader(UINT index);
	void SetPixelShader(UINT index);
	void SetGeometryShader(UINT index);
	void SetHullShader(UINT index);
	void SetDomainShader(UINT index);

	void Init(ID3D11DeviceContext*& device_context);
	void Exit();

};