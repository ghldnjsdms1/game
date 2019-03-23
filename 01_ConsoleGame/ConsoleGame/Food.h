#pragma once
#include "Define.h"
#include "Object.h"
#include "DoubleBuffer.h"

extern DoubleBuffer* g_pDB; // ������� �������� ��������

class Food : public Object{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	int		m_posX;
	int		m_posY;

public:
	void	Init(int x, int y);

public:
	Food();
	~Food();
};

