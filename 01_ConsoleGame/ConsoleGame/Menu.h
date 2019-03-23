#pragma once
#include "Scene.h"
#include "SceneMgr.h"
#include "DoubleBuffer.h"

extern bool g_bGameExit;
extern DoubleBuffer* g_pDB;
extern SceneMgr* g_pSM;

class Menu : public Scene
{
public:
	virtual void Init(SceneMgr* pSceneMgr);
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	void DrawMenu();

public:
	DWORD	m_SelectMenu = MENU_SEL_STAGE;
	DWORD	m_KeyTime;							// 키 입력시간 체크

public:
	Menu();
	~Menu();
};