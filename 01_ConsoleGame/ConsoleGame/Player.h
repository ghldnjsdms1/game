#pragma once
#include "Object.h"
#include "DoubleBuffer.h"
#include "Bullet.h"
extern DoubleBuffer* g_pDB; // 더블버퍼 전역변수 가져오기

class Player : public Object
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

private:
	// 캐릭터 모양
	int m_Char[5][5] = {
		{1,1,1,1,0},
		{1,1,0,0,0},
		{1,1,1,1,1},
		{1,1,0,0,0},
		{1,1,1,1,0}};

	// 캐릭터 위치
	int m_posX = 3;
	int m_posY = 2;

	// 총알 객체를 보관할 자료구조
	list<Bullet> m_BulletList;

public:
	Player();
	~Player();
};

