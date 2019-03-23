#pragma once
#include "Shape.h"
#include "DoubleBuffer.h"
#include "ShapeMgr.h"

extern DoubleBuffer* g_pDB;

class Shape_Rect : public Shape{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	DWORD	m_AutoTime;
	DWORD	m_KeyTime;
	int		m_posX;
	int		m_posY;

	void	MoveDown();
	void	MoveLeft();
	void	MoveRight();
	void	KeyUpdate();

public:
	Shape_Rect();
	virtual ~Shape_Rect();
};

