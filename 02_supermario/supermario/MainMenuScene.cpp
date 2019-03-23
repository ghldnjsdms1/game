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
	// 맵 크기 설정
	m_MapSize.x = 256;
	m_MapSize.y = 16;

	m_ScreenSize.x = m_MapSize.x * m_TileSize;					// 타일영역 가로 크기
	m_ScreenSize.y = m_MapSize.y * m_TileSize + m_TileSize;		// 타일영역 세로 크기


	m_ItemListSize.x = m_ScreenSize.x * 2;						// 아이템 리스트 가로 클릭 범위
	m_ItemListSize.y = m_ScreenSize.y + m_TileSize;				// 아이템 리스트 세로 클릭 범위

	InitMapData();

	m_Scroll.x = 0;
	m_Scroll.y = 0;

	// 타일맵 불러오기
	LoadMap();

	m_SpriteTime = 200; // 0.2초
	m_SpriteXIndex = 0;
	m_SpriteYIndex = 0;
	m_SpriteStartIndex = 0;
	m_SpriteEndIndex = 2;

	m_Image = ImageLoad(L"mario_maptile.bmp", 0, 0);

	if (m_Image == NULL) {
		Log("이미지 불러오기 실패!");
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

	// ESC키를 눌렀을 때 사각형 활성화
	if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
		//GameManager::GetGameManager()->GetSceneManager()->ChangeScene("PlayScene");
	}

	// Enter키를 눌렀을 때 사각형 활성화
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

	// 맵 타일 그리기
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

	// 맵 타일 인덱스를 가져옵니다.
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			inputFile >> m_Map[i][j];
		}
	}

	// 맵 충돌 타일 가져오기
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

	// 맵 타일 저장
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			outputFile << m_Map[i][j] << " ";
		}
		outputFile << std::endl;
	}

	// 맵 충돌타일 저장
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			outputFile << m_MapCollMap[i][j] << " ";
		}
		outputFile << std::endl;
	}
}
