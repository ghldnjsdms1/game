#include "MakeScene.h"
#include "GameManager.h"


MakeScene::MakeScene()
{
	//Init();
}


MakeScene::~MakeScene()
{
	//Destroy();
}

void MakeScene::Init()
{
	Log("make");
	// �� ũ�� ����
	m_MapSize.x = 256;
	m_MapSize.y = 16;

	m_TileSize = 28;

	m_ScreenSize.x = m_MapSize.x * m_TileSize;				// Ÿ�Ͽ��� ���� ũ��
	m_ScreenSize.y = m_MapSize.y * m_TileSize + m_TileSize;	// Ÿ�Ͽ��� ���� ũ��

															// ������ ����Ʈ Ŭ�� ����
	m_ItemListSize.x = m_ScreenSize.x * 2;
	m_ItemListSize.y = m_ScreenSize.y + m_TileSize;

	InitMapData();

	m_Scroll.x = 0;
	m_Scroll.y = 0;

	// Ÿ�ϸ� �ҷ�����
	LoadMap();

	LoadImg(L"mario_maptile.bmp", 0, 0);

	if (m_Image == NULL) {
		Log("�̹��� �ҷ����� ����!");
	}

	m_pPlayer = CharacterManager::GetPlayer();
}

void MakeScene::Update()
{
	if (m_pPlayer->m_currentScene != SCENE_MAKE) {
		m_pPlayer->m_currentScene = SCENE_MAKE;
	}

	//// ���� ����Ű Ŭ��
	//if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
	//	if (m_AddNum > 0) 
	//		m_AddNum--;
	//}
	//// ������ ����Ű Ŭ��
	//if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
	//	if (m_AddNum < m_MapMaxCount) 
	//		m_AddNum++;
	//}
	// ���� ����Ű Ŭ��
	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		if (m_AddNum > 0)
			m_AddNum--;
	}
	// �Ʒ��� ����Ű Ŭ��
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		if (m_AddNum < m_MapAcrossCountY - 1)
			m_AddNum++;
	}
	// ���� ����Ű Ŭ��
	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		if (m_Scroll.x > 0)
			m_Scroll.x -= m_TileSize;
	}
	// ������ ����Ű Ŭ��
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		if (m_Scroll.x < m_MapSize.x * m_TileSize)
			m_Scroll.x += m_TileSize;
	}
	// ���콺 ���� Ŭ��
	if (GetAsyncKeyState(VK_LBUTTON)) {
		POINT m_Posi = GameManager::GetGameManager()->GetMouseManager()->GetClientMousePosition();

		// �� Ÿ���� Ŭ������ ��(���� ����)
		if (m_Posi.x >= 0 && m_Posi.x <= m_ScreenSize.x &&
			m_Posi.y >= 0 && m_Posi.y <= m_ScreenSize.y) {
			Log("�� Ÿ�� Ŭ��!");

			int mX = (m_Posi.x + m_Scroll.x) / m_TileSize;
			int mY = m_Posi.y / m_TileSize;

			m_Map[mY][mX] = m_SelectNumber + m_AddNum * m_MapAcrossCountX;

			// �浹 Ÿ�� ����
			/*if (m_IsColl)	m_MapCollMap[mY][mX] = 1;
			else			m_MapCollMap[mY][mX] = 0;*/
			switch (m_IsColl)
			{
			case 0:
				m_MapCollMap[mY][mX] = 0;
				break;
			case 1:
				m_MapCollMap[mY][mX] = 1;
				break;
			case 2:
				m_MapCollMap[mY][mX] = 2;
				break;
			case 3:
				m_MapCollMap[mY][mX] = 3;
				break;
			case 4:
				m_MapCollMap[mY][mX] = 4;
				break;
			case 5:
				m_MapCollMap[mY][mX] = 5;
				break;
			case 6:
				m_MapCollMap[mY][mX] = 6;
				break;
			case 7:
				m_MapCollMap[mY][mX] = 7;
				break;
			}
		}

		// ������ ����Ʈ�� Ŭ������ �� (������ Ÿ�� ����)
		else if (m_Posi.x <= m_ItemListSize.x && m_Posi.y <= m_ItemListSize.y
			|| m_Posi.x <= m_ItemListSize.x && m_Posi.y <= m_ItemListSize.y + m_TileSize) {
			Log("������ ����Ʈ Ŭ��!");

			int mX = m_Posi.x / m_TileSize;
			int mY = m_Posi.y / m_TileSize;

			m_SelectNumber = (mY % 2 == 1) ? mX : mX + m_MapAcrossCount;
		}
	}

	// SŰ�� ������ �� ����
	if (GetAsyncKeyState(VK_S) & 0x0001) {
		// Ÿ�ϸ� ����
		SaveMap();
	}

	// CŰ�� ������ �� �浹 Ȱ��ȭ
	/*if (GetAsyncKeyState(0x43) & 0x0001) {
	m_IsColl = !m_IsColl;
	}*/

	if (GetAsyncKeyState(0x30) & 0x0001)	m_IsColl = 0;	// 0Ű�� ������ �� �浹 Ȱ��ȭ
	if (GetAsyncKeyState(0x31) & 0x0001)	m_IsColl = 1;	// 1Ű�� ������ �� �浹 Ȱ��ȭ
	if (GetAsyncKeyState(0x32) & 0x0001)	m_IsColl = 2;	// 2Ű�� ������ �� �浹 Ȱ��ȭ
	if (GetAsyncKeyState(0x33) & 0x0001)	m_IsColl = 3;	// 3Ű�� ������ �� �浹 Ȱ��ȭ
	if (GetAsyncKeyState(0x34) & 0x0001)	m_IsColl = 4;	// 4Ű�� ������ �� �浹 Ȱ��ȭ
	if (GetAsyncKeyState(0x35) & 0x0001)	m_IsColl = 5;	// 5Ű�� ������ �� �浹 Ȱ��ȭ
	if (GetAsyncKeyState(0x36) & 0x0001)	m_IsColl = 6;	// 6Ű�� ������ �� �浹 Ȱ��ȭ
	if (GetAsyncKeyState(0x37) & 0x0001)	m_IsColl = 7;	// 7Ű�� ������ �� �浹 Ȱ��ȭ

															// AŰ�� ������ �� �簢�� Ȱ��ȭ
															/*if (GetAsyncKeyState(0x41) & 0x0001) {
															m_IsRect = !m_IsRect;
															}*/

															// ESCŰ�� ������ �� �簢�� Ȱ��ȭ
	if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
		GameManager::GetGameManager()->GetSceneManager()->ChangeScene("MainMenuScene");
		GameManager::GetGameManager()->GetSceneManager()->DestroyScene("MakeScene");
	}
}

void MakeScene::Render(HDC memDC, HDC backMemDC)
{
	FillRect(backMemDC, &m_FillRect, (HBRUSH)GetStockObject(GRAY_BRUSH));

	// �� Ÿ�� �׸���
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			SelectObject(memDC, m_Image);

			// Ÿ�� �簢�� Ȱ��ȭ �Ǿ��� �� �� Ÿ�� �簢�� �׸���
			/*if (m_IsRect) {
			Rectangle(backMemDC, m_TileSize * j, m_TileSize * i, (m_TileSize * (j + 1)), (m_TileSize * (i + 1)));
			}*/
			TransparentBlt(
				backMemDC,
				m_TileSize * j - m_Scroll.x, m_TileSize * i, m_TileSize, m_TileSize,
				memDC,
				(m_Map[i][j] % m_MapAcrossCountX) * m_OriTileSize,
				(m_Map[i][j] / m_MapAcrossCountX) * m_OriTileSize,
				m_OriTileSize, m_OriTileSize, RGB(255, 246, 0));

			// �浹 Ÿ�� �׸���
			/*if (m_MapCollMap[i][j] == 1) {
			Ellipse(backMemDC, m_TileSize * j - m_Scroll.x, m_TileSize * i, (m_TileSize * j) + 20 - m_Scroll.x, (m_TileSize * i) + 20);
			}*/
			switch (m_MapCollMap[i][j])
			{
			case 0:
				//TextOut(backMemDC, m_TileSize * j - m_Scroll.x, m_TileSize * i, (LPCWSTR)"0", 1);
				break;
			case 1:
				TextOut(backMemDC, m_TileSize * j - m_Scroll.x, m_TileSize * i, (LPCWSTR)"1", 1);
				break;
			case 2:
				TextOut(backMemDC, m_TileSize * j - m_Scroll.x, m_TileSize * i, (LPCWSTR)"2", 1);
				break;
			case 3:
				TextOut(backMemDC, m_TileSize * j - m_Scroll.x, m_TileSize * i, (LPCWSTR)"3", 1);
				break;
			case 4:
				TextOut(backMemDC, m_TileSize * j - m_Scroll.x, m_TileSize * i, (LPCWSTR)"4", 1);
				break;
			case 5:
				TextOut(backMemDC, m_TileSize * j - m_Scroll.x, m_TileSize * i, (LPCWSTR)"5", 1);
				break;
			case 6:
				TextOut(backMemDC, m_TileSize * j - m_Scroll.x, m_TileSize * i, (LPCWSTR)"6", 1);
				break;
			case 7:
				TextOut(backMemDC, m_TileSize * j - m_Scroll.x, m_TileSize * i, (LPCWSTR)"7", 1);
				break;
			}

		}
	}

	// ������ ����Ʈ �׸���
	for (int j = 0; j < 2; ++j) {
		for (int i = 0; i < m_MapAcrossCount; ++i) {
			// Ÿ�� �簢�� Ȱ��ȭ �Ǿ��� �� �� Ÿ�� �簢�� �׸���
			/*if (m_IsRect) {
			Rectangle(backMemDC, m_TileSize * i, m_ScreenSize.y + (j * m_TileSize), m_TileSize * (i + 1), m_ScreenSize.y + ((j + 1) * m_TileSize));
			}*/
			TransparentBlt(
				backMemDC,
				m_TileSize * i, m_ScreenSize.y + (j * m_TileSize), m_TileSize, m_TileSize,
				memDC,
				(j == 0) ? i * m_OriTileSize : (i + m_MapAcrossCount) * m_OriTileSize,
				m_AddNum * m_OriTileSize,
				m_OriTileSize, m_OriTileSize, NULL);

		}
	}

	// ���õ� Ÿ�� �̹��� �׸���
	TransparentBlt(
		backMemDC,
		m_TileSize * m_MapAcrossCount + 20, m_ScreenSize.y,
		m_TileSize, m_TileSize,
		memDC,
		m_SelectNumber * m_OriTileSize,
		m_AddNum * m_OriTileSize,
		m_OriTileSize, m_OriTileSize, NULL);

	// �浹�� Ȱ��ȭ �Ǿ��� �� ���õ� Ÿ���̹��� ����
	/*if (m_IsColl)
	Ellipse(backMemDC, m_TileSize * m_MapAcrossCount + 20, m_ScreenSize.y,
	m_TileSize * m_MapAcrossCount + 40, m_ScreenSize.y + 20);*/
	switch (m_IsColl)
	{
	case 0:
		//TextOut(backMemDC, m_TileSize * m_MapAcrossCount + 20, m_ScreenSize.y, (LPCWSTR)"0", 1);
		break;
	case 1:
		TextOut(backMemDC, m_TileSize * m_MapAcrossCount + 20, m_ScreenSize.y, (LPCWSTR)"1", 1);
		break;
	case 2:
		TextOut(backMemDC, m_TileSize * m_MapAcrossCount + 20, m_ScreenSize.y, (LPCWSTR)"2", 1);
		break;
	case 3:
		TextOut(backMemDC, m_TileSize * m_MapAcrossCount + 20, m_ScreenSize.y, (LPCWSTR)"3", 1);
		break;
	case 4:
		TextOut(backMemDC, m_TileSize * m_MapAcrossCount + 20, m_ScreenSize.y, (LPCWSTR)"4", 1);
		break;
	case 5:
		TextOut(backMemDC, m_TileSize * m_MapAcrossCount + 20, m_ScreenSize.y, (LPCWSTR)"5", 1);
		break;
	case 6:
		TextOut(backMemDC, m_TileSize * m_MapAcrossCount + 20, m_ScreenSize.y, (LPCWSTR)"6", 1);
		break;
	case 7:
		TextOut(backMemDC, m_TileSize * m_MapAcrossCount + 20, m_ScreenSize.y, (LPCWSTR)"7", 1);
		break;
	}
}

void MakeScene::Destroy()
{
}

void MakeScene::LoadImg(LPCWSTR path, int width, int height)
{
	m_Image = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
}

void MakeScene::InitMapData()
{
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			m_Map[j][i] = 0;
			m_MapCollMap[i][j] = 0;
		}
	}
}

void MakeScene::LoadMap()
{
	//std::ifstream inputFile("mainmenu.txt");
	//std::ifstream inputFile("output.txt");
	//std::ifstream inputFile("playbonus.txt");
	std::ifstream inputFile("second.txt");

	// �� Ÿ�� �ε����� �����ɴϴ�.
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			inputFile >> m_Map[i][j];
		}
	}

	// �� �浹 Ÿ�� ��������
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			inputFile >> m_MapCollMap[i][j];
		}
	}

	inputFile.close();
}

void MakeScene::SaveMap()
{
	//std::ofstream outputFile("mainmenu.txt");
	//std::ofstream outputFile("output.txt");
	//std::ofstream outputFile("playbonus.txt");
	std::ofstream outputFile("second.txt");

	// �� Ÿ�� ����
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			outputFile << m_Map[i][j] << " ";
		}
		outputFile << std::endl;
	}

	// �� �浹Ÿ�� ����
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			outputFile << m_MapCollMap[i][j] << " ";
		}
		outputFile << std::endl;
	}
}
