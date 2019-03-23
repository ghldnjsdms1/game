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
	// 맵 크기 설정
	m_MapSize.x = 10;
	m_MapSize.y = 10;
	
	m_ScreenSize.x = m_MapSize.x * m_TileSize;		// 타일영역 가로 크기
	m_ScreenSize.y = m_MapSize.y * m_TileSize + 30;	// 타일영역 세로 크기

	// 아이템 리스트 클릭 범위
	m_ItemListSize.x = m_ScreenSize.x;
	m_ItemListSize.y = m_ScreenSize.y + m_TileSize;

	InitMapData();

	// 타일맵 불러오기
	LoadMap();

	LoadImg(L"tilemap.bmp", 0, 0);

	if (m_Image == NULL) {
		Log("이미지 불러오기 실패!");
	}
}

void FirstScene::Update()
{
	// 왼쪽 방향키 클릭
	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		if (m_AddNum > 0) m_AddNum--;
	}
	// 오른쪽 방향키 클릭
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		if (m_AddNum < m_MapMaxCount) m_AddNum++;
	}
	// 마우스 왼쪽 클릭
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001) {
		POINT m_Posi = GameManager::GetGameManager()->GetMouseManager()->GetClientMousePosition();
		
		// 맵 타일을 클릭했을 때(맵을 변경)
		if (m_Posi.x >= 0 && m_Posi.x <= m_ScreenSize.x &&
			m_Posi.y >= 0 && m_Posi.y <= m_ScreenSize.y) {
			Log("맵 타일 클릭!");

			int mX = m_Posi.x / m_TileSize;
			int mY = m_Posi.y / m_TileSize;

			m_Map[mY][mX] = m_SelectNumber;

			// 충돌 타일 변경
			if (m_IsColl)	m_MapCollMap[mY][mX] = 1;
			else			m_MapCollMap[mY][mX] = 0;
		}

		// 아이템 리스트를 클릭했을 때 (선택한 타일 변경)
		else if (m_Posi.x <= m_ItemListSize.x && m_Posi.y <= m_ItemListSize.y) {
			Log("아이템 리스트 클릭!");

			int mX = m_Posi.x / m_TileSize;
			m_SelectNumber = mX + m_AddNum;
		}
	}

	// S키를 눌렀을 때 저장
	if (GetAsyncKeyState(0x53) & 0x0001) {
		// 타일맵 저장
		SaveMap();
	}

	// C키를 눌렀을 때 충돌 활성화
	if (GetAsyncKeyState(0x43) & 0x0001) {
		// 타일맵 저장
		m_IsColl = !m_IsColl;
	}
}

void FirstScene::Render(HDC memDC, HDC backMemDC)
{
	// 맵 타일 그리기
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

			// 충돌 타일 그리기
			if (m_MapCollMap[i][j] == 1) {
				Ellipse(backMemDC, m_TileSize * j, m_TileSize * i, (m_TileSize * j) + 20, (m_TileSize * i) + 20);
			}
		}
	}

	// 아이템 리스트 그리기
	for (int i = 0; i < m_MapSize.x; ++i) {
		TransparentBlt(
			backMemDC,
			m_TileSize * i, m_ScreenSize.y, m_TileSize, m_TileSize,
			memDC,
			((i + m_AddNum) % m_MapAcrossCount) * m_OriTileSize,
			((i + m_AddNum) / m_MapAcrossCount) * m_OriTileSize,
			m_OriTileSize, m_OriTileSize, NULL);
	}

	// 선택된 타일 이미지 그리기
	TransparentBlt(
		backMemDC,
		m_TileSize * m_MapSize.x + 20, m_ScreenSize.y,
		m_TileSize, m_TileSize,
		memDC,
		(m_SelectNumber % m_MapAcrossCount) * m_OriTileSize,
		(m_SelectNumber / m_MapAcrossCount) * m_OriTileSize,
		m_OriTileSize, m_OriTileSize, NULL);

	// 충돌이 활성화 되었을 때 선택된 타일이미지 변경
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

void FirstScene::SaveMap()
{
	std::ofstream outputFile("output.txt");

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
