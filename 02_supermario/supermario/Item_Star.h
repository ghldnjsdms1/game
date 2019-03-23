#pragma once
#include "WndDefine.h"
#include "Object.h"

class Item_Star : public Object
{
public:
	Item_Star();
	~Item_Star();

public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC memDC, HDC backMemDC);

	void Scroll();			// 화면 스크롤
	void MoveUpdate();
};

