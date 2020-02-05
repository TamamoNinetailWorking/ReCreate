#include "ShaderManager.h"
#include <Shader/ShaderCast/ShaderCast.h>

using NKeyStruct = NShaderManager::KeyStruct;
using NVertexAndInput = NShaderManager::VertexShaderAndInputLayout;

using VertexMap = NShaderManager::VertexShaderMap;
using PixelMap = NShaderManager::PixelShaderMap;
using GeometryMap = NShaderManager::GeometryShaderMap;


template <typename Shader>
static bool ShaderList_Check(
	std::map<NKeyStruct, Shader>& map,
	const char* file,
	const char* func)
{
	if (map.count(NKeyStruct(file, func)))
	{
		return true;//Exists
	}
	else
	{
		return false;//Not Exists
	}

}

template <typename Shader>
static void ShaderList_Add(
	std::map<NKeyStruct, Shader>& map,
	Shader& pointer, const char* file_name, const char* func_name)
{
	map[NKeyStruct(file_name, func_name)] = pointer;
	return;
}

template <typename Shader>
static Shader ShaderList_Get(
	std::map<NKeyStruct, Shader>& map, const char* file_name, const char* func_name)
{
	return map[NKeyStruct(file_name, func_name)];
}

void CShaderManager::AllClear()
{
	m_pVertexShaderMap.clear();
	m_pInputLayoutMap.clear();
	m_pPixelShaderMap.clear();
	m_pGeometryShaderMap.clear();
	m_pHullShaderMap.clear();
	m_pDomainShaderMap.clear();
}

void CShaderManager::Init(ID3D11Device*& device,ID3D11DeviceContext*& device_context)
{
	m_pDevice = device;
	m_pDeviceContext = device_context;

	//ShaderCast().Init(m_pDevice, m_pDeviceContext);
}

void CShaderManager::Exit()
{
	AllClear();
}

bool CShaderManager::CheckWhetherVertexShaderIsAbleToChatch(const char* file_name, const char* func_name)
{
	return ShaderList_Check<ID3D11VertexShader*>(m_pVertexShaderMap, file_name, func_name);
}

bool CShaderManager::CheckWhetherInputLayoutIsAbleToChatch(const char* file_name, const char* func_name)
{
	return ShaderList_Check<ID3D11InputLayout*>(m_pInputLayoutMap, file_name, func_name);
}

bool CShaderManager::CheckWhetherPixelShaderIsAbleToChatch(const char* file_name, const char* func_name)
{
	return ShaderList_Check<ID3D11PixelShader*>(m_pPixelShaderMap, file_name, func_name);
}

bool CShaderManager::CheckWhetherGeometryShaderIsAbleToChatch(const char* file_name, const char* func_name)
{
	return ShaderList_Check<ID3D11GeometryShader*>(m_pGeometryShaderMap, file_name, func_name);
}

bool CShaderManager::CheckWhetherHullShaderIsAbleToChatch(const char* file_name, const char* func_name)
{
	return ShaderList_Check<ID3D11HullShader*>(m_pHullShaderMap, file_name, func_name);
}

bool CShaderManager::CheckWhetherDomainShaderIsAbleToChatch(const char* file_name, const char* func_name)
{
	return ShaderList_Check<ID3D11DomainShader*>(m_pDomainShaderMap, file_name, func_name);
}

bool CShaderManager::CheckWhetherComputeShaderIsAbleToChatch(const char* file_name, const char* func_name)
{
	return ShaderList_Check<ID3D11ComputeShader*>(m_pComputeShaderMap, file_name, func_name);
}

bool CShaderManager::GetVertexShader(const char* file_name, const char* func_name, ID3D11VertexShader*& pVertexShader, ID3D11InputLayout*& pInputLayout,ID3D11ClassLinkage*& pClassLinkage,bool use_class)
{
	if (CheckWhetherVertexShaderIsAbleToChatch(file_name, func_name))
	{
		//Exists.
		pVertexShader = ShaderList_Get<ID3D11VertexShader*>(m_pVertexShaderMap, file_name, func_name);
		pInputLayout = ShaderList_Get<ID3D11InputLayout*>(m_pInputLayoutMap, file_name, func_name);
		pClassLinkage = ShaderList_Get<ID3D11ClassLinkage*>(m_pVertexLinkMap, file_name, func_name);
		return true;
	}
	else
	{
		//Not Exists.
		if (ShaderCast().CreateVertexShader((char*)file_name, func_name, pVertexShader, pInputLayout,pClassLinkage,use_class))
		{
			ShaderList_Add <ID3D11VertexShader*>(m_pVertexShaderMap, pVertexShader, file_name, func_name);
			ShaderList_Add<ID3D11InputLayout*>(m_pInputLayoutMap, pInputLayout, file_name, func_name);
			ShaderList_Add<ID3D11ClassLinkage*>(m_pVertexLinkMap, pClassLinkage, file_name, func_name);
			return true;
		}
		else
		{
			//Targeted file is not exists.
			return false;
		}
	}
}

bool CShaderManager::GetPixelShader(const char* file_name, const char* func_name, ID3D11PixelShader*& pPixelShader,ID3D11ClassLinkage*& pClassLinkage,bool use_class)
{
	ID3D11PixelShader* PS;

	if (CheckWhetherPixelShaderIsAbleToChatch(file_name, func_name))
	{
		//Exists.
		PS = ShaderList_Get<ID3D11PixelShader*>(m_pPixelShaderMap, file_name, func_name);
		pPixelShader = PS;
		pClassLinkage = ShaderList_Get<ID3D11ClassLinkage*>(m_pPixelLinkMap, file_name, func_name);
		return true;
	}
	else
	{
		//Not Exists.
		if (ShaderCast().CreatePixelShader((char*)file_name, func_name, pPixelShader,pClassLinkage,use_class))
		{
			PS = pPixelShader;
			ShaderList_Add < ID3D11PixelShader*>(m_pPixelShaderMap, PS, file_name, func_name);
			ShaderList_Add<ID3D11ClassLinkage*>(m_pPixelLinkMap, pClassLinkage, file_name, func_name);
			return true;
		}
		else
		{
			//Targeted file is not exists.
			return false;
		}
	}
}

bool CShaderManager::GetGeometryShader(const char* file_name, const char* func_name, ID3D11GeometryShader*& pGeometryShader, ID3D11ClassLinkage*& pClassLinkage, bool use_class)
{
	ID3D11GeometryShader* GS;

	if (CheckWhetherGeometryShaderIsAbleToChatch(file_name, func_name))
	{
		//Exists.
		GS = ShaderList_Get<ID3D11GeometryShader*>(m_pGeometryShaderMap, file_name, func_name);
		pGeometryShader = GS;
		ShaderList_Get<ID3D11ClassLinkage*>(m_pGeometryLinkMap, file_name, func_name);
		return true;
	}
	else
	{
		//Not Exists.
		if (ShaderCast().CreateGeometryShader((char*)file_name, func_name, pGeometryShader,pClassLinkage,use_class))
		{
			GS = pGeometryShader;
			ShaderList_Add < ID3D11GeometryShader*>(m_pGeometryShaderMap, GS, file_name, func_name);
			ShaderList_Add<ID3D11ClassLinkage*>(m_pGeometryLinkMap, pClassLinkage, file_name, func_name);
			return true;
		}
		else
		{
			//Targeted file is not exists.
			return false;
		}
	}
}

bool CShaderManager::GetHullShader(const char* file_name, const char* func_name, ID3D11HullShader*& pHullShader,ID3D11ClassLinkage*& pClassLinkage,bool use_class)
{
	ID3D11HullShader* HS;

	if (CheckWhetherHullShaderIsAbleToChatch(file_name, func_name))
	{
		//Exists.
		HS = ShaderList_Get<ID3D11HullShader*>(m_pHullShaderMap, file_name, func_name);
		pHullShader = HS;
		ShaderList_Get<ID3D11ClassLinkage*>(m_pHullLinkMap, file_name, func_name);
		return true;
	}
	else
	{
		//Not Exists.
		if (ShaderCast().CreateHullShader((char*)file_name, func_name, pHullShader,pClassLinkage,use_class))
		{
			HS = pHullShader;
			ShaderList_Add < ID3D11HullShader*>(m_pHullShaderMap, HS, file_name, func_name);
			ShaderList_Add<ID3D11ClassLinkage*>(m_pHullLinkMap, pClassLinkage, file_name, func_name);
			return true;
		}
		else
		{
			//Targeted file is not exists.
			return false;
		}
	}
}

bool CShaderManager::GetDomainShader(const char* file_name, const char* func_name, ID3D11DomainShader*& pDomainShader,ID3D11ClassLinkage*& pClassLinkage,bool use_class)
{
	ID3D11DomainShader* DS;

	if (CheckWhetherDomainShaderIsAbleToChatch(file_name, func_name))
	{
		//Exists.
		DS = ShaderList_Get<ID3D11DomainShader*>(m_pDomainShaderMap, file_name, func_name);
		pDomainShader = DS;
		ShaderList_Get<ID3D11ClassLinkage*>(m_pDomainLinkMap, file_name, func_name);
		return true;
	}
	else
	{
		//Not Exists.
		if (ShaderCast().CreateDomainShader((char*)file_name, func_name, pDomainShader,pClassLinkage,use_class))
		{
			DS = pDomainShader;
			ShaderList_Add < ID3D11DomainShader*>(m_pDomainShaderMap, DS, file_name, func_name);
			ShaderList_Add<ID3D11ClassLinkage*>(m_pDomainLinkMap, pClassLinkage, file_name, func_name);
			return true;
		}
		else
		{
			//Targeted file is not exists.
			return false;
		}
	}
}

bool CShaderManager::GetComputeShader(const char* file_name, const char* func_name, ID3D11ComputeShader*& pComputeShader,ID3D11ClassLinkage*& pClassLinkage,bool use_class)
{
	ID3D11ComputeShader* CS;

	if (CheckWhetherComputeShaderIsAbleToChatch(file_name, func_name))
	{
		//Exists.
		CS = ShaderList_Get<ID3D11ComputeShader*>(m_pComputeShaderMap, file_name, func_name);
		pComputeShader = CS;
		ShaderList_Get<ID3D11ClassLinkage*>(m_pComputeLinkMap, file_name, func_name);
		return true;
	}
	else
	{
		//Not Exists.
		if (ShaderCast().CreateComputeShader((char*)file_name, func_name, pComputeShader,pClassLinkage,use_class))
		{
			CS = pComputeShader;
			ShaderList_Add < ID3D11ComputeShader*>(m_pComputeShaderMap, CS, file_name, func_name);
			ShaderList_Add<ID3D11ClassLinkage*>(m_pComputeLinkMap, pClassLinkage, file_name, func_name);
			return true;
		}
		else
		{
			//Targeted file is not exists.
			return false;
		}
	}
}