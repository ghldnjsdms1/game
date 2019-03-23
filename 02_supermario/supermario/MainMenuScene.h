#pragma once
#include "Scene.h"
#include <fstream>
#include "Player.h"
#include "CharacterManager.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene();
	~MainMenuScene();

public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC memDC, HDC backMemDC);
	virtual void Destroy();

	HBITMAP				ImageLoad(LPCWSTR path, int width, int height);			// �̹��� ���ϰ� �ҷ�������
	virtual void		LoadImg(LPCWSTR path, int width, int height);
	virtual void		InitMapData();
	virtual void		LoadMap();
	virtual void		SaveMap();

	Player* m_pPlayer;
};

