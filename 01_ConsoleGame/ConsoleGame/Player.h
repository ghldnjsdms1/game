#pragma once
#include "Object.h"
#include "DoubleBuffer.h"
#include "Bullet.h"
extern DoubleBuffer* g_pDB; // ������� �������� ��������

class Player : public Object
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

private:
	// ĳ���� ���
	int m_Char[5][5] = {
		{1,1,1,1,0},
		{1,1,0,0,0},
		{1,1,1,1,1},
		{1,1,0,0,0},
		{1,1,1,1,0}};

	// ĳ���� ��ġ
	int m_posX = 3;
	int m_posY = 2;

	// �Ѿ� ��ü�� ������ �ڷᱸ��
	list<Bullet> m_BulletList;

public:
	Player();
	~Player();
};

