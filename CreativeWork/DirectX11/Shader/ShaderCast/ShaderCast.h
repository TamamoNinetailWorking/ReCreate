#pragma once

#include <Singleton/Singleton.h>
#include <d3d11.h>

#pragma comment(lib,"d3d11.lib")

class CShaderCast : public CSingleton<CShaderCast>
{
	friend class CSingleton<CShaderCast>;
private:

	/* Device */
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

	HRESULT CompileShaderFromFile(char* szFilename, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	DXGI_FORMAT GetDxgiFormat(D3D_REGISTER_COMPONENT_TYPE type, BYTE mask);

	bool CreateSRVfromTGAFile(const char* filename, ID3D11ShaderResourceView** ppSRV);
	bool CreateSRVfromWICFile(const char* filename, ID3D11ShaderResourceView** ppSRV);

public:

	virtual ~CShaderCast() {}

	void Init(ID3D11Device*& device,ID3D11DeviceContext*& device_context);

	bool CreateVertexShader(
		char* szFileName,
		LPCSTR szFuncName,
		D3D11_INPUT_ELEMENT_DESC* layout,
		unsigned int numElements,
		ID3D11VertexShader*& pVertexShader,
		ID3D11InputLayout*& pInputLayout);

	bool CreateVertexShader(
		char* szFileName,
		LPCSTR szFuncName,
		ID3D11VertexShader*& pVertexShader,
		ID3D11InputLayout*& pInputLayout);

	bool CreatePixelShader(
		char*szFileName,
		LPCSTR szFuncName,
		ID3D11PixelShader*& pPixelShader);

	bool CreateGeometryShader(
		char*szFileName,
		LPCSTR szFuncName,
		ID3D11GeometryShader*& pGeometryShader);

	bool CreateHullShader(
		char* szFileName,
		LPCSTR szFuncName,
		ID3D11HullShader*& pHullShader);

	bool CreateDomainShader(
		char* szFileName,
		LPCSTR szFuncName,
		ID3D11DomainShader*& pDomainShader);

	bool CreateComputeShader(
		char* szFileName,
		LPCSTR szFuncName,
		ID3D11ComputeShader*& pComputeShader);

	bool CreateVertexBuffer(
		UINT stride,
		UINT VertexNum,
		void* pVertices,
		ID3D11Buffer*& pVertexBuffer);

	bool CreateIndexBuffer(
		UINT IndexNum,
		void* IndexData,
		ID3D11Buffer*& pIndexBuffer);

	bool CreateConstantBuffer(
		UINT ByteSize,
		ID3D11Buffer*& pConstantBuffer);

	bool CreateSamplerState(
		ID3D11SamplerState*& pSamplerState);

	bool CreateShaderResourceView(
		LPCSTR filename,
		ID3D11ShaderResourceView*& pSRV);
};