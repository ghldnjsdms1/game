#include "MainMenuScene.h"
#include "GameManager.h"


MainMenuScene::MainMenuScene()
{
	//Init();
}


MainMenuScene::~MainMenuScene()
{
	//Destroy();
}

void MainMenuScene::Init()
{
	Log("mainmenu");
	// �� ũ�� ����
	m_MapSize.x = 256;
	m_MapSize.y = 16;

	m_ScreenSize.x = m_MapSize.x * m_TileSize;					// Ÿ�Ͽ��� ���� ũ��
	m_ScreenSize.y = m_MapSize.y * m_TileSize + m_TileSize;		// Ÿ�Ͽ��� ���� ũ��


	m_ItemListSize.x = m_ScreenSize.x * 2;						// ������ ����Ʈ ���� Ŭ�� ����
	m_ItemListSize.y = m_ScreenSize.y + m_TileSize;				// ������ ����Ʈ ���� Ŭ�� ����

	InitMapData();

	m_Scroll.x = 0;
	m_Scroll.y = 0;

	// Ÿ�ϸ� �ҷ�����
	LoadMap();

	m_SpriteTime = 200; // 0.2��
	m_SpriteXIndex = 0;
	m_SpriteYIndex = 0;
	m_SpriteStartIndex = 0;
	m_SpriteEndIndex = 2;

	m_Image = ImageLoad(L"mario_maptile.bmp", 0, 0);

	if (m_Image == NULL) {
		Log("�̹��� �ҷ����� ����!");
	}

	m_pPlayer = CharacterManager::GetPlayer();
}

void MainMenuScene::Update()
{
	if (m_pPlayer->m_currentScene != SCENE_MAINMENU) {
		m_pPlayer->m_currentScene = SCENE_MAINMENU;
		/*m_pPlayer->SetPos(m_charPos.x, m_charPos.y);
		m_pPlayer->UpdateRect();*/
	}

	// ESCŰ�� ������ �� �簢�� Ȱ��ȭ
	if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
		//GameManager::GetGameManager()->GetSceneManager()->ChangeScene("PlayScene");
	}

	// EnterŰ�� ������ �� �簢�� Ȱ��ȭ
	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		GameManager::GetGameManager()->GetSceneManager()->ChangeScene("MakeScene");
		GameManager::GetGameManager()->GetSceneManager()->DestroyScene("MainMenuScene");
	}

	if (GetAsyncKeyState(VK_Q) & 0x0001) {
		GameManager::GetGameManager()->GetSceneManager()->ChangeScene("PlayScene");
		GameManager::GetGameManager()->GetSceneManager()->DestroyScene("MainMenuScene");
	}

	if (GetAsyncKeyState(VK_W) & 0x0001) {
		GameManager::GetGameManager()->GetSceneManager()->ChangeScene("PlayBonusScene");
		GameManager::GetGameManager()->GetSceneManager()->DestroyScene("MainMenuScene");
	}
	if (GetAsyncKeyState(VK_E) & 0x0001) {
		GameManager::GetGameManager()->GetSceneManager()->ChangeScene("SecondScene");
		GameManager::GetGameManager()->GetSceneManager()->DestroyScene("MainMenuScene");
	}
}

void MainMenuScene::Render(HDC memDC, HDC backMemDC)
{
	//FillRect(backMemDC, &m_FillRect, (HBRUSH)GetStockObject(GRAY_BRUSH));
	FillRect(backMemDC, &m_FillRect, CreateSolidBrush(RGB(104, 128, 248)));

	// �� Ÿ�� �׸���
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			SelectObject(memDC, m_Image);

			TransparentBlt(
				backMemDC,
				m_TileSize * j, m_TileSize * i, m_TileSize, m_TileSize,
				memDC,
				((m_Map[i][j] % m_MapAcrossCountX) * m_OriTileSize) + (m_SpriteXIndex * m_OriTileSize),
				(m_Map[i][j] / m_MapAcrossCountX) * m_OriTileSize + (m_SpriteYIndex * m_OriTileSize),
				m_OriTileSize, m_OriTileSize, RGB(255, 246, 0));
		}
	}

	//m_pPlayer->Render(backMemDC, memDC);
}

void MainMenuScene::Destroy()
{
}

HBITMAP MainMenuScene::ImageLoad(LPCWSTR path, int width, int height)
{
	return (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
}

void MainMenuScene::LoadImg(LPCWSTR path, int width, int height)
{
}

void MainMenuScene::InitMapData()
{
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			m_Map[i][j] = 0;
			m_MapCollMap[i][j] = 0;
		}
	}
}

void MainMenuScene::LoadMap()
{
	std::ifstream inputFile("mainmenu.txt");

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
			//inputFile >> m_pCollMap[j + i * m_MapSize.x];
		}
	}

	inputFile.close();
}

void MainMenuScene::SaveMap()
{
	std::ofstream outputFile("mainmenu.txt");

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
