#pragma once

class CObject;

class CComponent
{
public:

	CComponent() {}
	virtual ~CComponent() {}

	CObject* m_pParent;

	virtual void Start() {}
	virtual void Update() {}
	virtual void DrawUpdate() {}
	virtual void Draw() {}

};