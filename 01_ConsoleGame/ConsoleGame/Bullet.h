#pragma once
#include "Object.h"
#include "DoubleBuffer.h"
#include <list>

extern DoubleBuffer* g_pDB;

class Bullet : public Object
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	void Init(int x, int y);
	void SetBulletList(list<Bullet>* pBulletList);

private:
	list<Bullet>* m_pBulletList;

	bool m_Remove = false; // 삭제 체크
	int m_PosX = 0;
	int m_PosY = 0;

public:
	Bullet();
	~Bullet();
};


