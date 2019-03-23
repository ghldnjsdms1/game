#pragma once
#include "WndDefine.h"
#include "CharacterManager.h"

class ScrollManager
{
public:
	ScrollManager();
	~ScrollManager();

	// Variable__
private:
	POINT m_Scroll;
	POINT m_prevPos;

public:


	// Method__
private:


public:
	void Update();
	POINT GetScroll();
};

