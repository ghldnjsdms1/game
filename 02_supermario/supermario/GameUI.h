#pragma once
#include "Object.h"

class GameUI : public Object
{
public:
	GameUI();
	~GameUI();

public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC memDC, HDC backMemDC);
};

