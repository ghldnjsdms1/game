#pragma once
#include "WndDefine.h"
#include "Object.h"

class Item_Growup : public Object
{
public:
	Item_Growup();
	~Item_Growup();

public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC memDC, HDC backMemDC);

	void Scroll();			// ȭ�� ��ũ��
	void MoveUpdate();
};

