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
				g_pDB->WriteBuffer(0, 0, "������ �����մϴ�. �ƹ�Ű�� �����ּ���.");
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
	// 1. �ڽ� �׸���
	SetConsoleTextAttribute(g_pDB->GetBuffer(), RED);
	g_pDB->WriteBuffer(2, 1, "�������������������������������");
	for (int i = 2; i < 17; ++i)
	{
		g_pDB->WriteBuffer(2, i, "��");
		g_pDB->WriteBuffer(60, i, "��");
	}
	g_pDB->WriteBuffer(2, 17, "�������������������������������");
	SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);

	// 2. �޴� �׸���
	switch (m_SelectMenu)
	{
	case MENU_SEL_STAGE:
		SetConsoleTextAttribute(g_pDB->GetBuffer(), YELLOW);
		g_pDB->WriteBuffer(14, 5, "��");
		g_pDB->WriteBuffer(16, 5, "����� ����");

		SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
		g_pDB->WriteBuffer(16, 7, "�̷�Ż��");
		g_pDB->WriteBuffer(16, 9, "������ ����");
		g_pDB->WriteBuffer(16, 11, "���� ����");
		break;
	case MENU_SEL_STAGE2:
		SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
		g_pDB->WriteBuffer(16, 5, "����� ����");

		SetConsoleTextAttribute(g_pDB->GetBuffer(), YELLOW);
		g_pDB->WriteBuffer(14, 7, "��");
		g_pDB->WriteBuffer(16, 7, "�̷�Ż��");

		SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
		g_pDB->WriteBuffer(16, 9, "������ ����");
		g_pDB->WriteBuffer(16, 11, "���� ����");
		break;
	case MENU_SEL_STAGE3_EarthWarm:
		SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
		g_pDB->WriteBuffer(16, 5, "����� ����");		
		g_pDB->WriteBuffer(16, 7, "�̷�Ż��");
		SetConsoleTextAttribute(g_pDB->GetBuffer(), YELLOW);
		g_pDB->WriteBuffer(14, 9, "��");
		g_pDB->WriteBuffer(16, 9, "������ ����");
		SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
		g_pDB->WriteBuffer(16, 11, "���� ����");
		break;
	case MENU_GAME_EXIT:
		SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
		g_pDB->WriteBuffer(16, 5, "����� ����");
		g_pDB->WriteBuffer(16, 7, "�̷�Ż��");
		g_pDB->WriteBuffer(16, 9, "������ ����");
		SetConsoleTextAttribute(g_pDB->GetBuffer(), YELLOW);
		g_pDB->WriteBuffer(14, 11, "��");
		g_pDB->WriteBuffer(16, 11, "���� ����");
		break;
	}
}

Menu::Menu()
{
}


Menu::~Menu()
{
}
