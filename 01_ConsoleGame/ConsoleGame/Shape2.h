#pragma once
#include "Object.h"
#include "DoubleBuffer.h"

class Shape2 : public Object {
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	Shape2();
	~Shape2();
};

