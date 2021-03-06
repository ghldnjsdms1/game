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
	// 맵 크기 설정
	m_MapSize.x = 256;
	m_MapSize.y = 16;

	m_TileSize = 28;

	m_ScreenSize.x = m_MapSize.x * m_TileSize;				// 타일영역 가로 크기
	m_ScreenSize.y = m_MapSize.y * m_TileSize + m_TileSize;	// 타일영역 세로 크기

															// 아이템 리스트 클릭 범위
	m_ItemListSize.x = m_ScreenSize.x * 2;
	m_ItemListSize.y = m_ScreenSize.y + m_TileSize;

	InitMapData();

	m_Scroll.x = 0;
	m_Scroll.y = 0;

	// 타일맵 불러오기
	LoadMap();

	LoadImg(L"mario_maptile.bmp", 0, 0);

	if (m_Image == NULL) {
		Log("이미지 불러오기 실패!");
	}

	m_pPlayer = CharacterManager::GetPlayer();
}

void MakeScene::Update()
{
	if (m_pPlayer->m_currentScene != SCENE_MAKE) {
		m_pPlayer->m_currentScene = SCENE_MAKE;
	}

	//// 왼쪽 방향키 클릭
	//if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
	//	if (m_AddNum > 0) 
	//		m_AddNum--;
	//}
	//// 오른쪽 방향키 클릭
	//if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
	//	if (m_AddNum < m_MapMaxCount) 
	//		m_AddNum++;
	//}
	// 위쪽 방향키 클릭
	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		if (m_AddNum > 0)
			m_AddNum--;
	}
	// 아래쪽 방향키 클릭
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		if (m_AddNum < m_MapAcrossCountY - 1)
			m_AddNum++;
	}
	// 왼쪽 방향키 클릭
	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		if (m_Scroll.x > 0)
			m_Scroll.x -= m_TileSize;
	}
	// 오른쪽 방향키 클릭
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		if (m_Scroll.x < m_MapSize.x * m_TileSize)
			m_Scroll.x += m_TileSize;
	}
	// 마우스 왼쪽 클릭
	if (GetAsyncKeyState(VK_LBUTTON)) {
		POINT m_Posi = GameManager::GetGameManager()->GetMouseManager()->GetClientMousePosition();

		// 맵 타일을 클릭했을 때(맵을 변경)
		if (m_Posi.x >= 0 && m_Posi.x <= m_ScreenSize.x &&
			m_Posi.y >= 0 && m_Posi.y <= m_ScreenSize.y) {
			Log("맵 타일 클릭!");

			int mX = (m_Posi.x + m_Scroll.x) / m_TileSize;
			int mY = m_Posi.y / m_TileSize;

			m_Map[mY][mX] = m_SelectNumber + m_AddNum * m_MapAcrossCountX;

			// 충돌 타일 변경
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

		// 아이템 리스트를 클릭했을 때 (선택한 타일 변경)
		else if (m_Posi.x <= m_ItemListSize.x && m_Posi.y <= m_ItemListSize.y
			|| m_Posi.x <= m_ItemListSize.x && m_Posi.y <= m_ItemListSize.y + m_TileSize) {
			Log("아이템 리스트 클릭!");

			int mX = m_Posi.x / m_TileSize;
			int mY = m_Posi.y / m_TileSize;

			m_SelectNumber = (mY % 2 == 1) ? mX : mX + m_MapAcrossCount;
		}
	}

	// S키를 눌렀을 때 저장
	if (GetAsyncKeyState(VK_S) & 0x0001) {
		// 타일맵 저장
		SaveMap();
	}

	// C키를 눌렀을 때 충돌 활성화
	/*if (GetAsyncKeyState(0x43) & 0x0001) {
	m_IsColl = !m_IsColl;
	}*/

	if (GetAsyncKeyState(0x30) & 0x0001)	m_IsColl = 0;	// 0키를 눌렀을 때 충돌 활성화
	if (GetAsyncKeyState(0x31) & 0x0001)	m_IsColl = 1;	// 1키를 눌렀을 때 충돌 활성화
	if (GetAsyncKeyState(0x32) & 0x0001)	m_IsColl = 2;	// 2키를 눌렀을 때 충돌 활성화
	if (GetAsyncKeyState(0x33) & 0x0001)	m_IsColl = 3;	// 3키를 눌렀을 때 충돌 활성화
	if (GetAsyncKeyState(0x34) & 0x0001)	m_IsColl = 4;	// 4키를 눌렀을 때 충돌 활성화
	if (GetAsyncKeyState(0x35) & 0x0001)	m_IsColl = 5;	// 5키를 눌렀을 때 충돌 활성화
	if (GetAsyncKeyState(0x36) & 0x0001)	m_IsColl = 6;	// 6키를 눌렀을 때 충돌 활성화
	if (GetAsyncKeyState(0x37) & 0x0001)	m_IsColl = 7;	// 7키를 눌렀을 때 충돌 활성화

															// A키를 눌렀을 때 사각형 활성화
															/*if (GetAsyncKeyState(0x41) & 0x0001) {
															m_IsRect = !m_IsRect;
															}*/

															// ESC키를 눌렀을 때 사각형 활성화
	if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
		GameManager::GetGameManager()->GetSceneManager()->ChangeScene("MainMenuScene");
		GameManager::GetGameManager()->GetSceneManager()->DestroyScene("MakeScene");
	}
}

void MakeScene::Render(HDC memDC, HDC backMemDC)
{
	FillRect(backMemDC, &m_FillRect, (HBRUSH)GetStockObject(GRAY_BRUSH));

	// 맵 타일 그리기
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			SelectObject(memDC, m_Image);

			// 타일 사각형 활성화 되었을 때 각 타일 사각형 그리기
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

			// 충돌 타일 그리기
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

	// 아이템 리스트 그리기
	for (int j = 0; j < 2; ++j) {
		for (int i = 0; i < m_MapAcrossCount; ++i) {
			// 타일 사각형 활성화 되었을 때 각 타일 사각형 그리기
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

	// 선택된 타일 이미지 그리기
	TransparentBlt(
		backMemDC,
		m_TileSize * m_MapAcrossCount + 20, m_ScreenSize.y,
		m_TileSize, m_TileSize,
		memDC,
		m_SelectNumber * m_OriTileSize,
		m_AddNum * m_OriTileSize,
		m_OriTileSize, m_OriTileSize, NULL);

	// 충돌이 활성화 되었을 때 선택된 타일이미지 변경
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
