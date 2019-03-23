#include "DrawUI.h"



void DrawUI::Init(SceneMgr * pSceneMgr)
{
}

void DrawUI::Update(){
	if (GetAsyncKeyState(VK_UP))
	{
		m_SelectMenu = MENU_GAME_RETURN;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_SelectMenu = MENU_GAME_EXIT;
	}

	if (GetAsyncKeyState(VK_RETURN))
	{
		switch (m_SelectMenu)
		{
		case MENU_GAME_RETURN:
			m_GamePause = false;
			break;
		case MENU_GAME_EXIT:
			m_SelectMenu = MENU_GAME_RETURN;
			////////////////////////////////////////////////////
			switch (m_Menu.m_SelectMenu){
			case MENU_SEL_STAGE:
				break;
			case MENU_SEL_STAGE2:
				break;
			case MENU_SEL_STAGE3_EarthWarm:
				break;
			}
			////////////////////////////////////////////////////
			m_GamePause = !m_GamePause;
			g_pSM->ReserveChangeScene("Menu");
			break;
		}
	}
}

void DrawUI::Render(){
	// 1. UI 그릴 화면 초기화 (뒤에 비치지 않기 위해서)
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 11; j++)
		{
			g_pDB->WriteBuffer(12 + (i * 2), 4 + j, " ");
		}
	}
	
	// 2. UI 창 그리기
	SetConsoleTextAttribute(g_pDB->GetBuffer(), RED);
	g_pDB->WriteBuffer(12, 4, "■■■■■■■■■■■■■■■■■■■■");
	
	for (int i = 5; i < 14; ++i)
	{
		g_pDB->WriteBuffer(12, i, "■");
		g_pDB->WriteBuffer(50, i, "■");
	}
	
	g_pDB->WriteBuffer(12, 14, "■■■■■■■■■■■■■■■■■■■■");
	
	// 3. UI 메뉴
	switch (m_SelectMenu)
	{
	case MENU_GAME_RETURN:
		SetConsoleTextAttribute(g_pDB->GetBuffer(), YELLOW);
		g_pDB->WriteBuffer(26, 8, "▶");
		g_pDB->WriteBuffer(28, 8, "돌아가기");
	
		SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
		g_pDB->WriteBuffer(28, 10, "메인화면");
		break;
	case MENU_GAME_EXIT:
		SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
		g_pDB->WriteBuffer(28, 8, "돌아가기");
	
		SetConsoleTextAttribute(g_pDB->GetBuffer(), YELLOW);
		g_pDB->WriteBuffer(26, 10, "▶");
		g_pDB->WriteBuffer(28, 10, "메인화면");

		break;
	}
}

void DrawUI::Release()
{
}

void DrawUI::m_Pause() {
	if (GetAsyncKeyState(VK_ESCAPE) && GetTickCount() - m_KeyTime > 100)
	{
		m_KeyTime = GetTickCount();

		m_SelectMenu = MENU_GAME_RETURN;
		m_GamePause = !m_GamePause;
	}
}

DrawUI::DrawUI()
{
}


DrawUI::~DrawUI()
{
}
