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

	bool CreateClassLinkage(bool use_class, ID3D11ClassLinkage*& pClassLinkage);

	bool CreateVertexShader(
		char* szFileName,
		LPCSTR szFuncName,
		D3D11_INPUT_ELEMENT_DESC* layout,
		unsigned int numElements,
		ID3D11VertexShader*& pVertexShader,
		ID3D11InputLayout*& pInputLayout,
		ID3D11ClassLinkage*& pClassLinkage,
		bool use_class);

	bool CreateVertexShader(
		char* szFileName,
		LPCSTR szFuncName,
		ID3D11VertexShader*& pVertexShader,
		ID3D11InputLayout*& pInputLayout,
		ID3D11ClassLinkage*& pClassLinkage,
		bool use_class);

	bool CreatePixelShader(
		char*szFileName,
		LPCSTR szFuncName,
		ID3D11PixelShader*& pPixelShader,
		ID3D11ClassLinkage*& pClassLinkage,
		bool use_class);

	bool CreateGeometryShader(
		char*szFileName,
		LPCSTR szFuncName,
		ID3D11GeometryShader*& pGeometryShader,
		ID3D11ClassLinkage*& pClassLinkage,
		bool use_class);

	bool CreateHullShader(
		char* szFileName,
		LPCSTR szFuncName,
		ID3D11HullShader*& pHullShader,
		ID3D11ClassLinkage*& pClassLinkage,
		bool use_class);

	bool CreateDomainShader(
		char* szFileName,
		LPCSTR szFuncName,
		ID3D11DomainShader*& pDomainShader,
		ID3D11ClassLinkage*& pClassLinkage,
		bool use_class);

	bool CreateComputeShader(
		char* szFileName,
		LPCSTR szFuncName,
		ID3D11ComputeShader*& pComputeShader,
		ID3D11ClassLinkage*& pClassLinkage,
		bool use_class);

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

inline CShaderCast& ShaderCast()
{
	return CShaderCast::GetInstance();
}