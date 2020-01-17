#pragma once

#include <list>
#include <string>

typedef unsigned int UINT;
class CComponent;

class CObject
{
protected:

	std::list<CComponent*> m_pComponentList;
	std::string m_sObjectName;
	UINT m_nID;
	bool m_bStartFlag;
	bool m_bActiveFlag;

	void common_init(std::string name);

public:

	explicit CObject();
	CObject(std::string name);
	virtual ~CObject();

	virtual void Start();
	virtual void Update();
	virtual void DrawUpdate();
	virtual void Draw();

	template <class T>T*& GetComponent();
	template <class T>T*& AddComponent();

	std::string GetObjectName();
};