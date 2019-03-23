#pragma once
#include "WndDefine.h"
#include "Object.h"
#include <list>
//#include "Player.h"
//#include "CharacterManager.h"

class Monster2 : public Object
{
public:
	Monster2();
	virtual ~Monster2();

	// Variable__
private:
	list<Object>*	m_pMonsterList;

public:

	// Method__
private:

public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC memDC, HDC backMemDC);

	void Scroll();			// 화면 스크롤
	void SetPos(int x, int y);
	void	MoveUpdate();
	void CollUpdate(int dir);
	void DieMotion(int type);
};

