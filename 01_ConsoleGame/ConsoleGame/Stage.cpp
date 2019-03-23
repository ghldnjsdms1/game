#include "Stage.h"

void Stage::Init(SceneMgr * pSceneMgr)
{
	m_pSceneMgr = pSceneMgr;

	m_KeyTime = GetTickCount();
	m_Player.Init();
}

void Stage::Update()
{
	// 게임이 정지되어 있지않다면 플레이어 업데이트
	if (!m_DrawUI.m_GamePause)
		m_Player.Update();
	else
		m_DrawUI.Update();

	m_DrawUI.m_Pause();
}

void Stage::Render()
{
	DrawMap();

	m_Player.Render();

	if (m_DrawUI.m_GamePause) m_DrawUI.Render();
}

void Stage::Release()
{
	m_Player.Release();
}

void Stage::DrawMap()
{
	SetConsoleTextAttribute(g_pDB->GetBuffer(), CYAN);
	g_pDB->WriteBuffer(2, 1, "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");

	for (int i = 2; i < 17; ++i)
	{
		g_pDB->WriteBuffer(2, i, "■");
		g_pDB->WriteBuffer(60, i, "■");
	}

	g_pDB->WriteBuffer(2, 17, "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
}

Stage::Stage()
{
}


Stage::~Stage()
{
}
