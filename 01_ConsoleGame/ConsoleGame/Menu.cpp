#include "Menu.h"



void Menu::Init(SceneMgr * pSceneMgr)
{
	m_pSceneMgr = pSceneMgr;

	m_KeyTime = GetTickCount();
}

void Menu::Update()
{
	if (GetTickCount() - m_KeyTime > 150) {
		if (GetAsyncKeyState(VK_UP) && m_SelectMenu != 3) {
			--m_SelectMenu;
		}
		if (GetAsyncKeyState(VK_DOWN) && m_SelectMenu != 6) {
			++m_SelectMenu;
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			switch (m_SelectMenu) {
			case MENU_SEL_STAGE:
				//m_SelectMenu = MENU_SEL_STAGE;
				g_pSM->ReserveChangeScene("Stage");
				break;
			case MENU_SEL_STAGE2:
				//m_SelectMenu = MENU_SEL_STAGE;
				g_pSM->ReserveChangeScene("Stage2");
				break;
			case MENU_SEL_STAGE3_EarthWarm:
				//m_SelectMenu = MENU_SEL_STAGE;
				g_pSM->ReserveChangeScene("Stage3_EarthWarm");
				break;
			case MENU_GAME_EXIT:
				//m_SelectMenu = MENU_SEL_STAGE;
				g_bGameExit = true;
				SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
				g_pDB->WriteBuffer(0, 0, "게임을 종료합니다. 아무키나 눌러주세요.");
				break;
			}
		}
		m_KeyTime = GetTickCount();
	}
}

void Menu::Render()
{
	DrawMenu();
}

void Menu::Release()
{
}

void Menu::DrawMenu()
{
	// 1. 박스 그리기
	SetConsoleTextAttribute(g_pDB->GetBuffer(), RED);
	g_pDB->WriteBuffer(2, 1, "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	for (int i = 2; i < 17; ++i)
	{
		g_pDB->WriteBuffer(2, i, "■");
		g_pDB->WriteBuffer(60, i, "■");
	}
	g_pDB->WriteBuffer(2, 17, "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);

	// 2. 메뉴 그리기
	switch (m_SelectMenu)
	{
	case MENU_SEL_STAGE:
		SetConsoleTextAttribute(g_pDB->GetBuffer(), YELLOW);
		g_pDB->WriteBuffer(14, 5, "▶");
		g_pDB->WriteBuffer(16, 5, "비행기 게임");

		SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
		g_pDB->WriteBuffer(16, 7, "미로탈출");
		g_pDB->WriteBuffer(16, 9, "지렁이 게임");
		g_pDB->WriteBuffer(16, 11, "게임 종료");
		break;
	case MENU_SEL_STAGE2:
		SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
		g_pDB->WriteBuffer(16, 5, "비행기 게임");

		SetConsoleTextAttribute(g_pDB->GetBuffer(), YELLOW);
		g_pDB->WriteBuffer(14, 7, "▶");
		g_pDB->WriteBuffer(16, 7, "미로탈출");

		SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
		g_pDB->WriteBuffer(16, 9, "지렁이 게임");
		g_pDB->WriteBuffer(16, 11, "게임 종료");
		break;
	case MENU_SEL_STAGE3_EarthWarm:
		SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
		g_pDB->WriteBuffer(16, 5, "비행기 게임");		
		g_pDB->WriteBuffer(16, 7, "미로탈출");
		SetConsoleTextAttribute(g_pDB->GetBuffer(), YELLOW);
		g_pDB->WriteBuffer(14, 9, "▶");
		g_pDB->WriteBuffer(16, 9, "지렁이 게임");
		SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
		g_pDB->WriteBuffer(16, 11, "게임 종료");
		break;
	case MENU_GAME_EXIT:
		SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
		g_pDB->WriteBuffer(16, 5, "비행기 게임");
		g_pDB->WriteBuffer(16, 7, "미로탈출");
		g_pDB->WriteBuffer(16, 9, "지렁이 게임");
		SetConsoleTextAttribute(g_pDB->GetBuffer(), YELLOW);
		g_pDB->WriteBuffer(14, 11, "▶");
		g_pDB->WriteBuffer(16, 11, "게임 종료");
		break;
	}
}

Menu::Menu()
{
}


Menu::~Menu()
{
}
