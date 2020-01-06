#include "ShaderCast.h"

#include <locale.h>
#include <memory>
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/WICTextureLoader.h>

#pragma comment(lib,"DirectXTex.lib")

bool CShaderCast::CreateSRVfromTGAFile(const char* filename, ID3D11ShaderResourceView** ppSRV)
{
	HRESULT hr;
	wchar_t ws[512];
	size_t ret;

	setlocale(LC_CTYPE, "jpn");
	mbstowcs_s(&ret, ws, 512, filename, _TRUNCATE);

	DirectX::TexMetadata meta;
	DirectX::GetMetadataFromTGAFile(ws, meta);

	typename std::unique_ptr<DirectX::ScratchImage> image(new DirectX::ScratchImage);
	hr = LoadFromTGAFile(ws, &meta, *image);
	if (FAILED(hr))
	{
		return false;
	}

	//Create Shader ResourceView from Texture File
	hr = DirectX::CreateShaderResourceView(m_pDevice, image->GetImages(), image->GetImageCount(), meta, ppSRV);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool CShaderCast::CreateSRVfromWICFile(const char* filename, ID3D11ShaderResourceView** ppSRV)
{
	ID3D11Resource* texr = nullptr;

	wchar_t ws[512];
	size_t ret;

	setlocale(LC_CTYPE, "jpn");
	mbstowcs_s(&ret, ws, 512, filename, _TRUNCATE);

	//Read Texture from File
	HRESULT hr = DirectX::CreateWICTextureFromFile(
		m_pDevice,
		m_pDeviceContext,
		ws,
		&texr,
		ppSRV);

	if (FAILED(hr))
	{
		//MessageBox(NULL, "CreateWICTextureFromFile", "Error", MB_OK);
		return false;
	}

	return true;
}


bool CShaderCast::CreateShaderResourceView(LPCSTR filename, ID3D11ShaderResourceView*& pSRV)
{
	bool sts = false;

	sts = CreateSRVfromWICFile(filename, &pSRV);

	if (!sts)
	{
		//Failed to read texture from "WIC"File
		sts = CreateSRVfromTGAFile(filename, &pSRV);
		if (!sts)
		{
			MessageBox(NULL, "Failed to create texture from file.", "Error", MB_OK);
			return false;
		}
	}

	return true;
}