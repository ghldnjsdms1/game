#pragma once
#include "Object.h"
#include "DoubleBuffer.h"

class Shape1 : public Object{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	Shape1();
	~Shape1();
};

