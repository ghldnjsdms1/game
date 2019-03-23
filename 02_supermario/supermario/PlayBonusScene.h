#pragma once
#include "Scene.h"
#include <fstream>
#include "Player.h"
#include <list>
#include <map>
#include "Monster.h"
#include "Monster2.h"
#include "Item_Coin.h"
#include "Item_Growup.h"
#include "Item_Growup2.h"
#include "Item_Star.h"
#include "Item_WallBreak.h"
#include "CharacterManager.h"
#include "GameUI.h"

class PlayBonusScene : public Scene
{
public:
	PlayBonusScene();
	virtual ~PlayBonusScene();

	// Variable__
private:
	DWORD			m_dwTime;
	POINT			m_Scroll;
	Monster*		m_pMonster;
	list<Object*>	m_MonsterList;
	list<Object*>	m_ItemList;
	Player*			m_pPlayer;

	map<OBJECT_TYPE, Object*>			m_objectList;
	//map<OBJECT_TYPE, Object*>::iterator iter;
	list<Object*>::iterator				iter;
	list<Object*>::iterator				iter2;

	GameUI			m_pGameUI;

public:

	// Method__
private:


public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC memDC, HDC backMemDC);
	virtual void Destroy();

	HBITMAP				ImageLoad(LPCWSTR path, int width, int height);			// 이미지 편하게 불러오도록
	virtual void		LoadImg(LPCWSTR path, int width, int height);
	virtual void		InitMapData();
	virtual void		LoadMap();
	virtual void		SaveMap();

	bool CheckCollision(Object* object);

	int CheckCollisionTop(Object* object);
	int CheckCollisionBottom(Object* object);
	int CheckCollisionLeft(Object* object);
	int CheckCollisionRight(Object* object);

	void CollisionTop(Object* object);
	void CollisionBottom(Object* object);
	void CollisionLeft(Object* object);
	void CollisionRight(Object* object);

	void NoCollisionTop(Object* object);
	void NoCollisionBottom(Object* object);
	void NoCollisionLeft(Object* object);
	void NoCollisionRight(Object* object);

	bool CheckCollisionObject(Object* object, list<Object*>* objectList);
	bool CheckCollisionObject(list<Object*>* objectList);
	bool CheckCollisionObject(list<Object*>* objectList, list<Object*>* objectList2);
};
