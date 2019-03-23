#include "Stage2.h"

// 0 ������ �� �ִ� ����
// 1 ��
// 2 Ż�ⱸ
int tempMap[10][10]
{
	{ 1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,1 },
	{ 1,0,1,1,1,1,1,0,1,1 },
	{ 1,0,1,1,0,0,1,0,0,1 },
	{ 1,0,1,1,1,0,1,0,1,1 },
	{ 1,0,0,0,0,0,1,0,0,1 },
	{ 1,0,1,1,1,0,1,0,2,1 },
	{ 1,0,1,1,1,0,1,0,1,1 },
	{ 1,0,0,0,0,0,0,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1 }
};


Stage2::Stage2()
{
}

Stage2::~Stage2()
{
}

void Stage2::Init(SceneMgr * pSceneMgr)
{
}

void Stage2::Update()
{
	// ������ �����Ǿ� �����ʴٸ� �÷��̾� ������Ʈ
	if (!m_DrawUI.m_GamePause) {
		if (GetAsyncKeyState(VK_UP))
		{
			if (m_PlayerY > 0)
			{
				if (tempMap[m_PlayerY - 1][m_PlayerX] != 1) m_PlayerY--;
			}
		}

		if (GetAsyncKeyState(VK_DOWN))
		{
			if (m_PlayerY < 8)
			{
				if (tempMap[m_PlayerY + 1][m_PlayerX] != 1) m_PlayerY++;
			}
		}

		if (GetAsyncKeyState(VK_LEFT))
		{
			if (m_PlayerX > 0)
			{
				if (tempMap[m_PlayerY][m_PlayerX - 1] != 1) m_PlayerX--;
			}
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{
			if (m_PlayerX < 8)
			{
				if (tempMap[m_PlayerY][m_PlayerX + 1] != 1) m_PlayerX++;
			}
		}

		// �÷��̾ Ż�ⱸ�� �����ϸ� ���� ��ȯ
		if (tempMap[m_PlayerY][m_PlayerX] == 2)
		{
			g_pSM->ReserveChangeScene("Stage");
		}
	}
	else
		m_DrawUI.Update();

	m_DrawUI.m_Pause();
	
}

void Stage2::Render()
{
	SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			g_pDB->WriteBuffer(j * 2, i, GetTileData(tempMap[i][j]));
		}
	}

	SetConsoleTextAttribute(g_pDB->GetBuffer(), YELLOW);
	g_pDB->WriteBuffer(m_PlayerX * 2, m_PlayerY, "��");

	if (m_DrawUI.m_GamePause) m_DrawUI.Render();
}

void Stage2::Release()
{
}

char * Stage2::GetTileData(int index)
{
	switch (index)
	{
	case 0:  return "  ";
	case 1:  return "��";
	case 2:  return "��";
	}

	return "  ";
}
