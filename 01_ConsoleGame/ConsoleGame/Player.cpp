#include "Player.h"

void Player::Init()
{
	m_posX = 3;
	m_posY = 2;
}

void Player::Update()
{
	if (GetAsyncKeyState(VK_UP))
	{
		if (m_posY > 2) m_posY--;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		if (m_posY < 12) m_posY++;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (m_posX > 2) m_posX--;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (m_posX < 25) m_posX++;
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		Bullet tempBullet;

		tempBullet.Init(m_posX, m_posY);
		tempBullet.SetBulletList(&m_BulletList);

		m_BulletList.push_front(tempBullet);
	}

	// STL 자료구조들은 for문을 사용하실 때 iterator
	for (list<Bullet>::iterator iter = m_BulletList.begin(); iter != m_BulletList.end(); ++iter)
	{
		iter->Update();
	}
}

void Player::Render()
{
	for (int i = 0 ; i < 5; ++i)
	{
		for (int j = 0 ; j  < 5; ++j)
		{
			g_pDB->WriteBuffer((m_posX + i) * 2, m_posY + j, (m_Char[j][i]) ? "■" : "");
		}
	}

	for (list<Bullet>::iterator iter = m_BulletList.begin(); iter != m_BulletList.end(); ++iter)
	{
		iter->Render();
	}
}

void Player::Release()
{
}

Player::Player()
{
}


Player::~Player()
{
}
