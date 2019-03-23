#pragma once
#include "WndDefine.h"
#include "Object.h"
#include <list>

class Bullet : public Object
{
public:
	Bullet();
	virtual ~Bullet();

public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC memDC, HDC backMemDC);

	void Scroll();			// 화면 스크롤
	void SetPos(int x, int y, int dir);
	void UpdateRect();
	void	MoveUpdate();
	void DieMotion();

private:
	int m_bulletCount	= 0;

public:
	

};
