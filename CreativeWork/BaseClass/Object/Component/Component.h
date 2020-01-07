#pragma once

class Object;

class CComponent
{
public:

	CComponent() {}
	virtual ~CComponent() {}

	Object* m_pParent;

	virtual void Start() {}
	virtual void Update() {}
	virtual void Draw() {}

};