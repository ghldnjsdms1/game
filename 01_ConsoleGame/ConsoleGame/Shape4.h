#pragma once
#include "Object.h"
#include "DoubleBuffer.h"

class Shape4 : public Object {
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	Shape4();
	~Shape4();
};

