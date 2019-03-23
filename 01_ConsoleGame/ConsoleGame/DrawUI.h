#pragma once
#include "Scene.h"
#include "SceneMgr.h"
#include "DoubleBuffer.h"
#include "Menu.h"

extern bool g_bGameExit;
extern DoubleBuffer* g_pDB;
extern SceneMgr* g_pSM;

class DrawUI : public Scene{
public:
	virtual void Init(SceneMgr* pSceneMgr);
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void	m_Pause();							// 게임 일시정지

public:
	bool	m_GamePause = false;				// 일시정지 체크
	DWORD	m_SelectMenu = MENU_GAME_RETURN;	// 게임 메뉴 설정

private:
	Menu	m_Menu;
	DWORD	m_KeyTime;							// 키 입력시간 체크

public:
	DrawUI();
	~DrawUI();
};

