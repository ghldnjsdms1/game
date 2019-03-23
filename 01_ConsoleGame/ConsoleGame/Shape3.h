#pragma once
#include "Object.h"
#include "DoubleBuffer.h"

class Shape3 : public Object {
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	Shape3();
	~Shape3();
};

