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

	void	m_Pause();							// ���� �Ͻ�����

public:
	bool	m_GamePause = false;				// �Ͻ����� üũ
	DWORD	m_SelectMenu = MENU_GAME_RETURN;	// ���� �޴� ����

private:
	Menu	m_Menu;
	DWORD	m_KeyTime;							// Ű �Է½ð� üũ

public:
	DrawUI();
	~DrawUI();
};

