#pragma once

#include <vector>
#include <Object/Component/Component.h>
#include <Utility/Utility.h>
#include <Utility/EnderUtility.h>

template
<typename VertexBuffer,typename IndexBuffer,typename MaterialBuffer,typename MaterialIndexBuffer,typename ConstantBuffer,typename ShaderResource>
class CDrawer : public CComponent
{
protected:

	/* Vertex */
	VertexBuffer* m_pVertexBuffer;
	IndexBuffer* m_pIndexBuffer;
	
	/* Material */
	std::vector<MaterialBuffer*> m_pMaterialContainer;
	MaterialIndexBuffer* m_pMaterialIndexBuffer;

	/* ShaderResource */
	std::vector<ConstantBuffer*> m_pBufferContainer;
	std::vector<ShaderResource*> m_pSRVContainer;

	virtual void construction() {
		m_pVertexBuffer = nullptr;
		m_pIndexBuffer = nullptr;

		m_pMaterialContainer = nullptr;
		m_pMaterialIndexBuffer = nullptr;

		m_pBufferContainer = nullptr;
		m_pSRVContainer = nullptr;
	}

public:

	CDrawer() { construction(); }
	virtual ~CDrawer3D() { Exit(); };

	virtual void Exit()
	{
		ReleaseVector(m_pSRVContainer);
		ReleaseVector(m_pBufferContainer);
		Release(m_pMaterialIndexBuffer);
		ReleaseVector(m_pMaterialContainer);
		Release(m_pIndexBuffer);
		Release(m_pVertexBuffer);
	}

	VertexBuffer*& GetVertexBuffer() { return m_pVertexBuffer; }
	IndexBuffer*& GetIndexBuffer() { return m_pIndexBuffer; }
	MaterialIndexBuffer*& GetMaterialIndexBuffer() 
	{ return m_pMaterialIndexBuffer; }

	MaterialBuffer*& GetMaterialBuffer(int index = 0) 
	{ 
		return GetTemplate<MaterialBuffer*>(m_pMaterialContainer, index);
	}

	ConstantBuffer*& GetConstantBuffer(int index = 0) 
	{ 
		return GetTemplate<ConstantBuffer*>(m_pBufferContainer, index);
	}

	ShaderResource*& GetShaderResource(int index = 0) 
	{ 
		return GetTemplate<ShaderResource*>(m_pSRVContainer, index);
	}
};