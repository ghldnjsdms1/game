#pragma once
#include "Object.h"
#include "DoubleBuffer.h"

class Shape6 : public Object {
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	Shape6();
	~Shape6();
};

