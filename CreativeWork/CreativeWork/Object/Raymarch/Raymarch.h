#pragma once

#include <Object/Base/Object.h>

class CRaymarch : public CObject
{
protected:

	void init_component();

public:

	virtual void Start();
	virtual void Update();

};