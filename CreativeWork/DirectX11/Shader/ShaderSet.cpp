#include "ShaderSet.h"
#include <Shader/ShaderManager/ShaderManager.h>
#include <Utility/EnderUtility.h>

template<class Tempus>
static Tempus TemplateGetter(std::vector<Tempus> substance, UINT index)
{
	if (substance.size() > index)
	{
		return substance[index];
	}
	else
	{
		//Index Out of Range
		return nullptr;
	}
}

ID3D11VertexShader* CShaderSet::GetVertexShader(UINT index)
{
	return TemplateGetter<ID3D11VertexShader*>(m_vVertexShader, index);
}

ID3D11InputLayout* CShaderSet::GetInputLayout(UINT index)
{
	return TemplateGetter<ID3D11InputLayout*>(m_vInputLayout, index);
}

ID3D11PixelShader* CShaderSet::GetPixelShader(UINT index)
{
	return TemplateGetter<ID3D11PixelShader*>(m_vPixelShader, index);
}

ID3D11GeometryShader* CShaderSet::GetGeometryShader(UINT index)
{
	return TemplateGetter<ID3D11GeometryShader*>(m_vGeometryShader, index);
}

ID3D11HullShader* CShaderSet::GetHullShader(UINT index)
{
	return TemplateGetter<ID3D11HullShader*>(m_vHullShader, index);
}

ID3D11DomainShader* CShaderSet::GetDomainShader(UINT index)
{
	return TemplateGetter<ID3D11DomainShader*>(m_vDomainShader, index);
}


bool CShaderSet::CreateVertexShader(const char* file_name, const char* func_name,bool use_class)
{
	ID3D11VertexShader* vertex_shader;
	ID3D11InputLayout* input_layout;
	ID3D11ClassLinkage* pClassLinkage;
	if (CShaderManager::GetInstance().GetVertexShader(file_name, func_name, vertex_shader, input_layout,pClassLinkage,use_class))
	{
		//Created.
		m_vVertexShader.push_back(vertex_shader);
		m_vInputLayout.push_back(input_layout);
		m_vVertexLink.push_back(pClassLinkage);
		return true;
	}
	else
	{
		MessageBox(NULL, "FileName or FuncName is a fault.", "CShaderSet CreateVertexShader", MB_OK);
		return false;
	}
}

bool CShaderSet::CreatePixelShader(const char* file_name, const char* func_name,bool use_class)
{
	ID3D11PixelShader* pixel_shader;
	ID3D11ClassLinkage* pClassLinkage;
	if (CShaderManager::GetInstance().GetPixelShader(file_name, func_name, pixel_shader,pClassLinkage,use_class))
	{
		//Created.
		m_vPixelShader.push_back(pixel_shader);
		return true;
	}
	else
	{
		MessageBox(NULL, "FileName or FuncName is a fault.", "CShaderSet CreatePixelShader", MB_OK);
		return false;
	}
}

bool CShaderSet::CreateGeometryShader(const char* file_name, const char* func_name,bool use_class)
{
	ID3D11GeometryShader* geometry_shader;
	ID3D11ClassLinkage* pClassLinkage;
	if (CShaderManager::GetInstance().GetGeometryShader(file_name, func_name, geometry_shader,pClassLinkage,use_class))
	{
		//Created.
		m_vGeometryShader.push_back(geometry_shader);
		return true;
	}
	else
	{
		MessageBox(NULL, "FileName or FuncName is a fault.", "CShaderSet CreateGeometryShader", MB_OK);
		return false;
	}
}

bool CShaderSet::CreateHullShader(const char* file_name, const char* func_name,bool use_class)
{
	ID3D11HullShader* hull_shader;
	ID3D11ClassLinkage* pClassLinkage;
	if (CShaderManager::GetInstance().GetHullShader(file_name, func_name, hull_shader,pClassLinkage, use_class))
	{
		//Created.
		m_vHullShader.push_back(hull_shader);
		return true;
	}
	else
	{
		MessageBox(NULL, "FileName or FuncName is a fault.", "CShaderSet CreateHullShader", MB_OK);
		return false;
	}
}

bool CShaderSet::CreateDomainShader(const char* file_name, const char* func_name,bool use_class)
{
	ID3D11DomainShader* domain_shader;
	ID3D11ClassLinkage* pClassLinkage;
	if (CShaderManager::GetInstance().GetDomainShader( file_name, func_name, domain_shader, pClassLinkage, use_class))
	{
		//Created.
		m_vDomainShader.push_back(domain_shader);
		return true;
	}
	else
	{
		MessageBox(NULL, "FileName or FuncName is a fault.", "CShaderSet CreateDomainShader", MB_OK);
		return false;
	}
}

void CShaderSet::SetVertexShader(UINT index)
{
	m_pDeviceContext->VSSetShader(GetVertexShader(index), NULL, 0);
	m_pDeviceContext->IASetInputLayout(GetInputLayout(index));
}

void CShaderSet::SetPixelShader(UINT index)
{
	m_pDeviceContext->PSSetShader(GetPixelShader(index), NULL, 0);
}

void CShaderSet::SetGeometryShader(UINT index)
{
	m_pDeviceContext->GSSetShader(GetGeometryShader(index), NULL, 0);
}

void CShaderSet::SetHullShader(UINT index)
{
	m_pDeviceContext->HSSetShader(GetHullShader(index), NULL, 0);
}

void CShaderSet::SetDomainShader(UINT index)
{
	m_pDeviceContext->DSSetShader(GetDomainShader(index), NULL, 0);
}

void CShaderSet::Init(ID3D11DeviceContext*& device_context)
{
	m_pDeviceContext = device_context;
}

void CShaderSet::Exit()
{
	ReleaseVector(m_vDomainShader);
	ReleaseVector(m_vGeometryShader);
	ReleaseVector(m_vHullShader);
	ReleaseVector(m_vPixelShader);
	ReleaseVector(m_vInputLayout);
	ReleaseVector(m_vVertexShader);
}