#include "FirstScene.h"
#include "GameManager.h"


FirstScene::FirstScene()
{
	Init();
}


FirstScene::~FirstScene()
{
}

void FirstScene::Init()
{
	// �� ũ�� ����
	m_MapSize.x = 10;
	m_MapSize.y = 10;
	
	m_ScreenSize.x = m_MapSize.x * m_TileSize;		// Ÿ�Ͽ��� ���� ũ��
	m_ScreenSize.y = m_MapSize.y * m_TileSize + 30;	// Ÿ�Ͽ��� ���� ũ��

	// ������ ����Ʈ Ŭ�� ����
	m_ItemListSize.x = m_ScreenSize.x;
	m_ItemListSize.y = m_ScreenSize.y + m_TileSize;

	InitMapData();

	// Ÿ�ϸ� �ҷ�����
	LoadMap();

	LoadImg(L"tilemap.bmp", 0, 0);

	if (m_Image == NULL) {
		Log("�̹��� �ҷ����� ����!");
	}
}

void FirstScene::Update()
{
	// ���� ����Ű Ŭ��
	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		if (m_AddNum > 0) m_AddNum--;
	}
	// ������ ����Ű Ŭ��
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		if (m_AddNum < m_MapMaxCount) m_AddNum++;
	}
	// ���콺 ���� Ŭ��
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001) {
		POINT m_Posi = GameManager::GetGameManager()->GetMouseManager()->GetClientMousePosition();
		
		// �� Ÿ���� Ŭ������ ��(���� ����)
		if (m_Posi.x >= 0 && m_Posi.x <= m_ScreenSize.x &&
			m_Posi.y >= 0 && m_Posi.y <= m_ScreenSize.y) {
			Log("�� Ÿ�� Ŭ��!");

			int mX = m_Posi.x / m_TileSize;
			int mY = m_Posi.y / m_TileSize;

			m_Map[mY][mX] = m_SelectNumber;

			// �浹 Ÿ�� ����
			if (m_IsColl)	m_MapCollMap[mY][mX] = 1;
			else			m_MapCollMap[mY][mX] = 0;
		}

		// ������ ����Ʈ�� Ŭ������ �� (������ Ÿ�� ����)
		else if (m_Posi.x <= m_ItemListSize.x && m_Posi.y <= m_ItemListSize.y) {
			Log("������ ����Ʈ Ŭ��!");

			int mX = m_Posi.x / m_TileSize;
			m_SelectNumber = mX + m_AddNum;
		}
	}

	// SŰ�� ������ �� ����
	if (GetAsyncKeyState(0x53) & 0x0001) {
		// Ÿ�ϸ� ����
		SaveMap();
	}

	// CŰ�� ������ �� �浹 Ȱ��ȭ
	if (GetAsyncKeyState(0x43) & 0x0001) {
		// Ÿ�ϸ� ����
		m_IsColl = !m_IsColl;
	}
}

void FirstScene::Render(HDC memDC, HDC backMemDC)
{
	// �� Ÿ�� �׸���
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			SelectObject(memDC, m_Image);

			TransparentBlt(
				backMemDC,
				m_TileSize * j, m_TileSize * i, m_TileSize, m_TileSize,
				memDC,
				(m_Map[i][j] % m_MapAcrossCount) * m_OriTileSize,
				(m_Map[i][j] / m_MapAcrossCount) * m_OriTileSize,
				m_OriTileSize, m_OriTileSize, NULL);

			// �浹 Ÿ�� �׸���
			if (m_MapCollMap[i][j] == 1) {
				Ellipse(backMemDC, m_TileSize * j, m_TileSize * i, (m_TileSize * j) + 20, (m_TileSize * i) + 20);
			}
		}
	}

	// ������ ����Ʈ �׸���
	for (int i = 0; i < m_MapSize.x; ++i) {
		TransparentBlt(
			backMemDC,
			m_TileSize * i, m_ScreenSize.y, m_TileSize, m_TileSize,
			memDC,
			((i + m_AddNum) % m_MapAcrossCount) * m_OriTileSize,
			((i + m_AddNum) / m_MapAcrossCount) * m_OriTileSize,
			m_OriTileSize, m_OriTileSize, NULL);
	}

	// ���õ� Ÿ�� �̹��� �׸���
	TransparentBlt(
		backMemDC,
		m_TileSize * m_MapSize.x + 20, m_ScreenSize.y,
		m_TileSize, m_TileSize,
		memDC,
		(m_SelectNumber % m_MapAcrossCount) * m_OriTileSize,
		(m_SelectNumber / m_MapAcrossCount) * m_OriTileSize,
		m_OriTileSize, m_OriTileSize, NULL);

	// �浹�� Ȱ��ȭ �Ǿ��� �� ���õ� Ÿ���̹��� ����
	if (m_IsColl) 
		Ellipse(backMemDC, m_TileSize * m_MapSize.x + 20, m_ScreenSize.y, 
		m_TileSize * m_MapSize.x + 40, m_ScreenSize.y + 20);

}

void FirstScene::Destroy()
{
}

void FirstScene::LoadImg(LPCWSTR path, int width, int height)
{
	m_Image = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
}

void FirstScene::InitMapData()
{
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			m_Map[j][i] = 0;
			m_MapCollMap[j][i] = 0;
		}
	}
}

void FirstScene::LoadMap()
{
	std::ifstream inputFile("output.txt");

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

void FirstScene::SaveMap()
{
	std::ofstream outputFile("output.txt");

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
