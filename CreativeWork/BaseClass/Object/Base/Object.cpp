#include "Object.h"
#include <Object/Component/Component.h>
#include <Object/ObjectManager/ObjectManager.h>

using namespace std;

void CObject::common_init(string name)
{
	m_bStartFlag = false;
	m_bActiveFlag = false;
	m_sObjectName = name;
}

CObject::CObject()
{
	m_nID = ObjectManager().SetObject(this);

	string name;
	name = string("Object");
	name += string("(") + to_string(m_nID) + string(")");

	common_init(name);
}

CObject::CObject(std::string name)
{
	m_nID = ObjectManager().SetObject(this);
	common_init(name);
}

CObject::~CObject()
{
	for (auto com : m_pComponentList)
	{
		delete com;
	}
}

void CObject::Start()
{
	m_bStartFlag = true;
	return;
}

void CObject::Update()
{
	if (!m_bStartFlag)
	{
		Start();
	}

	for (auto com : m_pComponentList)
	{
		com->Update();
	}

	return;
}

void CObject::DrawUpdate()
{
	for (auto com : m_pComponentList)
	{
		com->DrawUpdate();
	}
}

void CObject::Draw()
{
	for (auto com : m_pComponentList)
	{
		com->Draw();
	}
}



std::string CObject::GetObjectName()
{
	return m_sObjectName;
}