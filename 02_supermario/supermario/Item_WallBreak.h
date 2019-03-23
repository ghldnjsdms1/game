#pragma once
#include "WndDefine.h"
#include "Object.h"

class Item_WallBreak : public Object
{
public:
	Item_WallBreak();
	~Item_WallBreak();

public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC memDC, HDC backMemDC);

	void Direct(int dir);

	void Scroll();			// 화면 스크롤
	void MoveUpdate();
};

