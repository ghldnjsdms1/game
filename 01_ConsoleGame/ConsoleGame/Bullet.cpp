#include "Bullet.h"

void Bullet::Init()
{
}

void Bullet::Update()
{
	if (m_PosX >= 30) Release();
}

void Bullet::Render()
{
	if (m_PosX < 30)
	{
		g_pDB->WriteBuffer(m_PosX * 2, m_PosY, "¡Ü");
		++m_PosX;
	}
}

void Bullet::Release()
{
	m_Remove = true;
}

void Bullet::Init(int x, int y)
{
	m_PosX = x + 5;
	m_PosY = y + 2;
}

void Bullet::SetBulletList(list<Bullet>* pBulletList)
{
	m_pBulletList = pBulletList;
}

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}
