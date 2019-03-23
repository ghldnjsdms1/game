#pragma once
#include "Shape.h"
#include "DoubleBuffer.h"
#include "ShapeMgr.h"

extern DoubleBuffer* g_pDB;

class Shape_Stick : public Shape{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	//ShapeMgr*	m_pShapeMgr;


public:
	Shape_Stick();
	~Shape_Stick();
};

