#include "SecondScene.h"
#include "GameManager.h"
//#include "CharacterManager.h"

SecondScene::SecondScene()
{
	//Init();
}


SecondScene::~SecondScene()
{
	Log("플레이씬 소멸자");
	//Destroy();
}

void SecondScene::Init()
{
	Log("secondScene");
	// 맵 크기 설정
	m_MapSize.x = 256;
	m_MapSize.y = 16;

	m_ScreenSize.x = m_MapSize.x * m_TileSize;					// 타일영역 가로 크기
	m_ScreenSize.y = m_MapSize.y * m_TileSize + m_TileSize;	// 타일영역 세로 크기


	m_ItemListSize.x = m_ScreenSize.x * 2;						// 아이템 리스트 가로 클릭 범위
	m_ItemListSize.y = m_ScreenSize.y + m_TileSize;				// 아이템 리스트 세로 클릭 범위

	InitMapData();

	m_Scroll.x = 0;
	m_Scroll.y = 0;

	//m_pCollMap = new DWORD [m_MapSize.x * m_MapSize.y];

	// 타일맵 불러오기
	LoadMap();

	//LoadImg(L"mario_maptile.bmp", 0, 0);
	m_Image = ImageLoad(L"mario_maptile.bmp", 0, 0);
	m_ImageItem = ImageLoad(L"mario_item.bmp", 0, 0);

	if (m_Image == NULL) {
		Log("이미지 불러오기 실패!");
	}

	if (m_ImageItem == NULL) {
		Log("아이템 이미지 불러오기 실패!");
	}

	// 스프라이트 정보를 초기화합니다.
	m_SpriteTime = 200; // 0.2초
	m_SpriteXIndex = 0;
	m_SpriteYIndex = 0;
	m_SpriteStartIndex = 0;
	m_SpriteEndIndex = 2;

	m_wallType = WALL_NONE;
	m_wallState = false;
	m_wallCount = 0;

	m_gamePause = false;
	m_keyTime = GetTickCount();

	m_pPlayer = CharacterManager::GetPlayer();

	m_objectList.insert(pair<OBJECT_TYPE, Object*>(MONSTER1, new Monster));
	m_objectList.insert(pair<OBJECT_TYPE, Object*>(ITEM_COIN, new Item_Coin));
	m_objectList.insert(pair<OBJECT_TYPE, Object*>(ITEM_GROWUP1, new Item_Growup));
	m_objectList.insert(pair<OBJECT_TYPE, Object*>(ITEM_GROWUP2, new Item_Growup2));
	m_objectList.insert(pair<OBJECT_TYPE, Object*>(ITEM_STAR, new Item_Star));
	m_objectList.insert(pair<OBJECT_TYPE, Object*>(ITEM_WALLBREAK, new Item_WallBreak));

	//if (m_objectList.find(MONSTER1) != m_objectList.end()) {
	/*m_MonsterList.push_back(new Monster);
	m_MonsterList.push_back(new Monster2);*/
	//}
	m_MonsterList.push_back(new Monster2);
	iter = m_MonsterList.end();
	iter--;
	dynamic_cast<Monster2*>(*iter)->SetPos(100, 100);

	m_charPos.x = 105;
	m_charPos.y = 462;

	for (int i = 0; i < 100; ++i)
		if (m_monsterCheck[i] == true)
			m_monsterCheck[i] = false;
}

void SecondScene::Update()
{
	if (m_pPlayer->m_currentScene != SCENE_SECOND) {
		m_pPlayer->SceneInit(SCENE_SECOND, m_charPos.x, m_charPos.y, true, m_pPlayer->m_CharLevel, false);
		m_pPlayer->ScrollInit(0, 0);
	}

	if (!m_gamePause) {
		// 플레이어
		m_pPlayer->Update();

		if ((m_pPlayer->m_CharLevel > -1 || m_pPlayer->m_secure) && m_pPlayer->m_Rect.top >= 0) {
			CheckCollision(m_pPlayer);		// 충돌체크
		}

		if (!m_pPlayer->m_collPause) {
			if (m_pPlayer->m_CharLevel == -1) {
				GameManager::GetGameManager()->GetSceneManager()->ChangeScene("GameOverScene");
				GameManager::GetGameManager()->GetSceneManager()->DestroyScene("SecondScene");
			}

			if (m_pPlayer->m_PosX > 7920) {
				m_pPlayer->ClearScene();
				/*GameManager::GetGameManager()->GetSceneManager()->ChangeScene("MainMenuScene");
				GameManager::GetGameManager()->GetSceneManager()->DestroyScene("PlayScene");*/
			}

			// 미사일
			iter = m_pPlayer->m_BulletList.begin();
			for (; iter != m_pPlayer->m_BulletList.end(); iter++) {
				if ((*iter)->m_UseCollision)
					CheckCollision(*iter);
				/*if ((*iter)->m_chkColl) {
				delete *iter;
				m_pPlayer->m_BulletList.erase(iter);
				break;
				}*/
			}

			// 몬스터
			iter = m_MonsterList.begin();
			for (; iter != m_MonsterList.end(); ++iter)
			{
				(*iter)->Update();
				if ((*iter)->m_UseCollision) {
					CheckCollision(*iter);
				}

				if ((*iter)->m_CharLevel == 0) {
					if ((*iter)->DieTimer() == true) {
						delete *iter;
						m_MonsterList.erase(iter);
						break;
					}
				}
			}

			if (m_pPlayer->m_UseCollision) {
				CheckCollisionObject(m_pPlayer, &m_MonsterList);
			}
			else {
				m_pPlayer->DontCollision();
				if (!m_pPlayer->m_UseCollision) {

				}
			}


			// 아이템
			iter = m_ItemList.begin();
			for (; iter != m_ItemList.end(); ++iter)
			{
				(*iter)->Update();

				if ((*iter)->m_UseCollision) {
					CheckCollision(*iter);
				}
			}
			if (m_pPlayer->m_UseCollision)
				CheckCollisionObject(m_pPlayer, &m_ItemList);

			CheckCollisionObject(&m_MonsterList);

			CheckCollisionObject(&m_MonsterList, &m_pPlayer->m_BulletList);

			// 미사일
			iter = m_pPlayer->m_BulletList.begin();
			for (; iter != m_pPlayer->m_BulletList.end(); iter++) {
				if ((*iter)->m_chkColl && (*iter)->GetSpriteYIndex() == (*iter)->GetSpriteEndIndex()) {
					delete *iter;
					m_pPlayer->m_BulletList.erase(iter);
					break;
				}
			}

			BaseUpdate();
		}
		else {
			m_pPlayer->CollPauseTime();
		}
	}

	ScreenExcept(m_pPlayer, &m_MonsterList);
	ScreenExcept(m_pPlayer, &m_ItemList);
	ScreenExcept(m_pPlayer, &m_pPlayer->m_BulletList);

	Pause();
}

void SecondScene::Render(HDC memDC, HDC backMemDC)
{
	FillRect(backMemDC, &m_FillRect, (HBRUSH)GetStockObject(BLACK_BRUSH));

	m_Scroll = m_pPlayer->m_Scroll;
	// 맵 타일 그리기
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			SelectObject(memDC, m_Image);

			if (m_Map[i][j] % m_MapAcrossCountX == 24 && (m_Map[i][j] / m_MapAcrossCountX) % 2 == 0 && m_Map[i][j] / m_MapAcrossCountX < 8) {
				TransparentBlt(
					backMemDC,
					m_TileSize * j - m_Scroll.x, m_TileSize * i, m_TileSize, m_TileSize,
					memDC,
					((m_Map[i][j] % m_MapAcrossCountX) * m_OriTileSize) + (m_SpriteXIndex * m_OriTileSize),
					(m_Map[i][j] / m_MapAcrossCountX) * m_OriTileSize + (m_SpriteYIndex * m_OriTileSize),
					m_OriTileSize, m_OriTileSize, RGB(255, 246, 0));
			}
			else if (m_Map[i][j] % m_MapAcrossCountX == 24 && (m_Map[i][j] / m_MapAcrossCountX) % 2 == 1 && m_Map[i][j] / m_MapAcrossCountX < 8) {
				TransparentBlt(
					backMemDC,
					m_TileSize * j - m_Scroll.x, m_TileSize * i, m_TileSize, m_TileSize,
					memDC,
					((m_Map[i][j] % m_MapAcrossCountX) * m_OriTileSize) + (m_SpriteXIndex * m_OriTileSize),
					(m_Map[i][j] / m_MapAcrossCountX) * m_OriTileSize + (m_SpriteYIndex * m_OriTileSize),
					m_OriTileSize, m_OriTileSize, RGB(255, 246, 0));
			}
			else if (m_Map[i][j] % m_MapAcrossCountX == 2 && (m_Map[i][j] / m_MapAcrossCountX) % 2 == 0 && m_Map[i][j] / m_MapAcrossCountX < 8) {
				if (m_wallCount <= 16) {
					switch (m_wallState)
					{
					case 0:
						m_wallCount -= 2;
						//Log("m_wallCount = ", m_wallCount);
						break;
					case 1:
						m_wallCount += 2;
						break;
					}
					TransparentBlt(
						backMemDC,
						m_TileSize * j - m_Scroll.x, m_TileSize * i - m_wallCount, m_TileSize, m_TileSize,
						memDC,
						(m_Map[i][j] % m_MapAcrossCountX) * m_OriTileSize,
						(m_Map[i][j] / m_MapAcrossCountX) * m_OriTileSize,
						m_OriTileSize, m_OriTileSize, RGB(255, 246, 0));
					if (m_wallCount == 16)	m_wallState = false;
					if (m_wallCount == 0) m_Map[i][j] = 67;
				}
			}
			else if (m_Map[i][j] % m_MapAcrossCountX == 3 && (m_Map[i][j] / m_MapAcrossCountX) % 2 == 0 && m_Map[i][j] / m_MapAcrossCountX < 8) {
				if (m_wallCount <= 16) {
					switch (m_wallState)
					{
					case 0:
						m_wallCount -= 2;
						break;
					case 1:
						m_wallCount += 2;
						break;
					}
					TransparentBlt(
						backMemDC,
						m_TileSize * j - m_Scroll.x, m_TileSize * i - m_wallCount, m_TileSize, m_TileSize,
						memDC,
						(m_Map[i][j] % m_MapAcrossCountX) * m_OriTileSize,
						(m_Map[i][j] / m_MapAcrossCountX) * m_OriTileSize,
						m_OriTileSize, m_OriTileSize, RGB(255, 246, 0));
					if (m_wallCount == 16)	m_wallState = false;
					if (m_wallCount == 0) m_Map[i][j] = 27;
				}
			}
			else if (m_Map[i][j] % m_MapAcrossCountX == 29 && (m_Map[i][j] / m_MapAcrossCountX) % 2 == 0 && m_Map[i][j] / m_MapAcrossCountX < 8) {
				TransparentBlt(
					backMemDC,
					m_TileSize * j - m_Scroll.x, m_TileSize * i, m_TileSize, m_TileSize,
					memDC,
					((m_Map[i][j] % m_MapAcrossCountX) * m_OriTileSize) + (m_SpriteXIndex * m_OriTileSize),
					(m_Map[i][j] / m_MapAcrossCountX) * m_OriTileSize + (m_SpriteYIndex * m_OriTileSize),
					m_OriTileSize, m_OriTileSize, RGB(255, 246, 0));
			}
			else {
				TransparentBlt(
					backMemDC,
					m_TileSize * j - m_Scroll.x, m_TileSize * i, m_TileSize, m_TileSize,
					memDC,
					(m_Map[i][j] % m_MapAcrossCountX) * m_OriTileSize,
					(m_Map[i][j] / m_MapAcrossCountX) * m_OriTileSize,
					m_OriTileSize, m_OriTileSize, RGB(255, 246, 0));
			}

		}
	}
	//BaseRender(memDC, backMemDC);

	m_pGameUI.Render(memDC, backMemDC);

	m_pPlayer->Render(memDC, backMemDC);

	/*iter = m_MonsterList.begin();
	for (; iter != m_MonsterList.end(); ++iter)
	{
		(*iter)->Render(memDC, backMemDC);
	}*/

	iter = m_ItemList.begin();
	for (; iter != m_ItemList.end(); ++iter)
	{
		(*iter)->Render(memDC, backMemDC);
	}

	/*if (m_pPlayer->m_PosX > 240 && m_pPlayer->m_PosX < 340 && !m_monsterCheck[0]) {
		m_monsterCheck[0] = true;
		m_MonsterList.push_back(new Monster);
		iter = m_MonsterList.end();
		iter--;
		dynamic_cast<Monster*>(*iter)->SetPos(m_pPlayer->m_PosX, m_pPlayer->m_PosY);
	}
	else if (m_pPlayer->m_PosX > 1400 && m_pPlayer->m_PosX < 1500 && !m_monsterCheck[1]) {
		m_monsterCheck[1] = true;
		m_MonsterList.push_back(new Monster);
		iter = m_MonsterList.end();
		iter--;
		dynamic_cast<Monster*>(*iter)->SetPos(m_pPlayer->m_PosX, m_pPlayer->m_PosY);
		m_MonsterList.push_back(new Monster);
		iter = m_MonsterList.end();
		iter--;
		dynamic_cast<Monster*>(*iter)->SetPos(m_pPlayer->m_PosX + 50, m_pPlayer->m_PosY);
	}
	else if (m_pPlayer->m_PosX > 2600 && m_pPlayer->m_PosX < 2700 && !m_monsterCheck[2]) {
		m_monsterCheck[2] = true;
		m_MonsterList.push_back(new Monster);
		iter = m_MonsterList.end();
		iter--;
		dynamic_cast<Monster*>(*iter)->SetPos(m_pPlayer->m_PosX, m_pPlayer->m_PosY);
		m_MonsterList.push_back(new Monster);
		iter = m_MonsterList.end();
		iter--;
		dynamic_cast<Monster*>(*iter)->SetPos(m_pPlayer->m_PosX + 50, m_pPlayer->m_PosY);
	}
	else if (m_pPlayer->m_PosX > 3300 && m_pPlayer->m_PosX < 3400 && !m_monsterCheck[3]) {
		m_monsterCheck[3] = true;
		m_MonsterList.push_back(new Monster);
		iter = m_MonsterList.end();
		iter--;
		dynamic_cast<Monster*>(*iter)->SetPos(m_pPlayer->m_PosX, m_pPlayer->m_PosY);
		m_MonsterList.push_back(new Monster);
		iter = m_MonsterList.end();
		iter--;
		dynamic_cast<Monster*>(*iter)->SetPos(m_pPlayer->m_PosX + 50, m_pPlayer->m_PosY);
	}
	else if (m_pPlayer->m_PosX > 3800 && m_pPlayer->m_PosX < 3900 && !m_monsterCheck[4]) {
		m_monsterCheck[4] = true;
		m_MonsterList.push_back(new Monster2);
		iter = m_MonsterList.end();
		iter--;
		dynamic_cast<Monster2*>(*iter)->SetPos(m_pPlayer->m_PosX, m_pPlayer->m_PosY);
	}
	else if (m_pPlayer->m_PosX > 4300 && m_pPlayer->m_PosX < 4400 && !m_monsterCheck[5]) {
		m_monsterCheck[5] = true;
		m_MonsterList.push_back(new Monster);
		iter = m_MonsterList.end();
		iter--;
		dynamic_cast<Monster*>(*iter)->SetPos(m_pPlayer->m_PosX, m_pPlayer->m_PosY);
		m_MonsterList.push_back(new Monster);
		iter = m_MonsterList.end();
		iter--;
		dynamic_cast<Monster*>(*iter)->SetPos(m_pPlayer->m_PosX + 50, m_pPlayer->m_PosY);
	}*/
}

void SecondScene::Destroy()
{
	Log("플레이씬 디스트로이");
	for (auto it = m_objectList.begin(); it != m_objectList.end(); it++) {
		delete it->second;
	}

	/*for (auto it = m_MonsterList.begin(); it != m_MonsterList.end(); ) {
		it = m_MonsterList.erase(it);
	}*/

	for (auto it = m_ItemList.begin(); it != m_ItemList.end(); ) {
		it = m_ItemList.erase(it);
	}
}

HBITMAP SecondScene::ImageLoad(LPCWSTR path, int width, int height)
{
	return (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
}

void SecondScene::LoadImg(LPCWSTR path, int width, int height)
{
}

void SecondScene::InitMapData()
{
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			m_Map[i][j] = 0;
			m_MapCollMap[i][j] = 0;
		}
	}
}

void SecondScene::LoadMap()
{
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
			//inputFile >> m_pCollMap[j + i * m_MapSize.x];
		}
	}

	inputFile.close();
}

void SecondScene::SaveMap()
{
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

bool SecondScene::CheckCollision(Object * object)
{
	// 플레이어 충돌처리
	if (object->m_Gravity > 0 && object->m_ItemType != 2) {
		switch (CheckCollisionTop(object))
		{
		case 0:
			NoCollisionTop(object);
			break;
		case 1:
			CollisionTop(object);
			break;
		case 2:
			//CollisionTop(object);
			break;
		case 7:
			dynamic_cast<Player*>(object)->m_coinCount++;
			break;
		}
	}
	else if (object->m_Gravity <= 0) {
		switch (CheckCollisionBottom(object))
		{
		case 0:
			NoCollisionBottom(object);
			break;
		case 1:
			CollisionBottom(object);
			break;
		case 2:
			//CollisionBottom(object);
			break;
		case 7:
			dynamic_cast<Player*>(object)->m_coinCount++;
			break;
		}
	}
	object->UpdateRect();
	switch (CheckCollisionLeft(object))
	{
	case 0:
		NoCollisionLeft(object);
		break;
	case 1:
		CollisionLeft(object);
		switch (object->m_ObjectType)
		{
		case 0:
			break;
		case 1:
			object->m_DirLeftRight = 0;
			break;
		case 2:
			object->m_DirLeftRight = 0;
			break;
		case 3:
			object->m_chkColl = true;
			object->SetSprite(7, 9, 9, 11, 200);
			object->SetCollInit(36, 36, false, 0);
			object->SetImgSizeInit(16, 16);
			break;
		}
		break;
	case 2:
		//CollisionLeft(object);
		break;
	case 7:
		dynamic_cast<Player*>(object)->m_coinCount++;
		break;
	}
	object->UpdateRect();
	switch (CheckCollisionRight(object))
	{
	case 0:
		NoCollisionRight(object);
		break;
	case 1:
		CollisionRight(object);
		switch (object->m_ObjectType)
		{
		case 0:
			break;
		case 1:
			object->m_DirLeftRight = 1;
			break;
		case 2:
			object->m_DirLeftRight = 1;
			break;
		case 3:
			object->m_chkColl = true;
			object->SetSprite(7, 9, 9, 11, 200);
			object->SetCollInit(36, 36, false, 0);
			object->SetImgSizeInit(16, 16);
			break;
		}
		break;
	case 2:
		//CollisionRight(object);
		break;
	case 7:
		dynamic_cast<Player*>(object)->m_coinCount++;
		break;
	}

	object->UpdateRect();
	return true;
}

int SecondScene::CheckCollisionTop(Object * object)
{
	POINT tempPoint;
	RECT tempRect;
	RECT tempCollRect;

	// 윗방향 충돌체크
	tempPoint.x = object->m_PosX / m_TileSize;
	tempPoint.y = object->m_Rect.top / m_TileSize;

	tempRect.left = tempPoint.x * m_TileSize;
	tempRect.top = tempPoint.y * m_TileSize;
	tempRect.right = (tempPoint.x + 1) * m_TileSize;
	tempRect.bottom = (tempPoint.y + 1) * m_TileSize;

	if (m_MapCollMap[tempPoint.y][tempPoint.x] != 0 && m_MapCollMap[tempPoint.y][tempPoint.x] != 7) {
		if (IntersectRect(&tempCollRect, &tempRect, &object->m_Rect)) {
			Log("위 3!");
			object->m_PosY += (tempPoint.y + 1) * m_TileSize - object->m_Rect.top;
			object->UpdateRect();

			switch (m_MapCollMap[tempPoint.y][tempPoint.x])
			{
			case 1:
				Log("1");

				return 1;
			case 2:
				Log("2");
				if (object->m_CharLevel == 0) {
					m_Map[tempPoint.y][tempPoint.x] = 68;
					m_wallType = WALL_DONT_BREAK;
					m_wallState = true;
				}
				else {
					m_Map[tempPoint.y][tempPoint.x] = 29;
					m_MapCollMap[tempPoint.y][tempPoint.x] = 0;
					m_wallType = WALL_BREAK;
					m_wallState = true;

					if (m_objectList.find(ITEM_WALLBREAK) != m_objectList.end()) {

						m_ItemList.push_back(new Item_WallBreak);
						m_ItemList.push_back(new Item_WallBreak);
						m_ItemList.push_back(new Item_WallBreak);
						m_ItemList.push_back(new Item_WallBreak);
						m_ItemList.push_back(new Item_WallBreak);

						iter = m_ItemList.end();
						for (int i = 0; i < 5; i++) {
							iter--;
							(*iter)->m_PosX = (tempRect.left + tempRect.right) / 2;
							(*iter)->m_PosY = (tempRect.top + tempRect.bottom) / 2;
							(*iter)->UpdateRect();
						}
						iter = m_ItemList.end();
						iter--;
						(*iter)->m_wallBreakDir = 4;	// 좌하
						(*iter)->Direct(4);
						iter--;
						(*iter)->m_wallBreakDir = 3;	// 우하
						(*iter)->Direct(3);
						iter--;
						(*iter)->m_wallBreakDir = 2;	// 우상
						(*iter)->Direct(2);
						iter--;
						(*iter)->m_wallBreakDir = 1;	// 좌상
						(*iter)->Direct(1);
						iter--;
						(*iter)->m_wallBreakDir = 5;	// 중립
						(*iter)->Direct(5);
					}
				}

				return 1;
			case 3:Log("3");
				CharacterManager::GetPlayer()->m_coinCount++;
				CharacterManager::GetPlayer()->m_totalScore += 200;
				m_Map[tempPoint.y][tempPoint.x] = 3;
				m_MapCollMap[tempPoint.y][tempPoint.x] = 1;

				m_wallType = WALL_ITEM_COIN;
				if (m_objectList.find(ITEM_COIN) != m_objectList.end()) {
					m_ItemList.push_back(new Item_Coin);
				}

				iter = m_ItemList.end();
				iter--;
				(*iter)->m_PosX = (tempRect.left + tempRect.right) / 2;
				(*iter)->m_PosY = (tempRect.top + tempRect.bottom) / 2;
				(*iter)->UpdateRect();

				m_wallState = true;
				break;
			case 4:Log("4");
				m_Map[tempPoint.y][tempPoint.x] = 3;
				m_MapCollMap[tempPoint.y][tempPoint.x] = 1;

				m_wallType = WALL_ITEM_GROWUP;
				switch (object->m_CharLevel)
				{
				case 0:
					if (m_objectList.find(ITEM_GROWUP1) != m_objectList.end()) {
						m_ItemList.push_back(new Item_Growup);
					}
					break;
				case 1:
					if (m_objectList.find(ITEM_GROWUP2) != m_objectList.end()) {
						m_ItemList.push_back(new Item_Growup2);
					}
					break;
				case 2:
					if (m_objectList.find(ITEM_GROWUP2) != m_objectList.end()) {
						m_ItemList.push_back(new Item_Growup2);
					}
					break;
				}

				iter = m_ItemList.end();
				iter--;
				(*iter)->m_PosX = (tempRect.left + tempRect.right) / 2;
				(*iter)->m_PosY = (tempRect.top + tempRect.bottom) / 2;
				(*iter)->UpdateRect();

				m_wallState = true;
				break;
			case 5:Log("5");
				m_Map[tempPoint.y][tempPoint.x] = 3;
				m_MapCollMap[tempPoint.y][tempPoint.x] = 1;

				m_wallType = WALL_ITEM_STAR;
				if (m_objectList.find(ITEM_STAR) != m_objectList.end()) {
					m_ItemList.push_back(new Item_Star);
				}

				iter = m_ItemList.end();
				iter--;
				(*iter)->m_PosX = (tempRect.left + tempRect.right) / 2;
				(*iter)->m_PosY = (tempRect.top + tempRect.bottom) / 2;
				(*iter)->UpdateRect();

				m_wallState = true;
				break;
			}
			return 1;
		}
	}
	else if (m_MapCollMap[tempPoint.y][tempPoint.x] == 7 && object->m_ObjectType == 0) {
		if (IntersectRect(&tempCollRect, &tempRect, &object->m_Rect)) {
			m_Map[tempPoint.y][tempPoint.x] = 28;
			m_MapCollMap[tempPoint.y][tempPoint.x] = 0;
			return 7;
		}
	}
	return 0;
}

int SecondScene::CheckCollisionBottom(Object * object)
{
	POINT tempPoint;
	RECT tempRect;
	RECT tempCollRect;

	// 아랫방향 충돌체크
	tempPoint.x = object->m_Rect.left / m_TileSize;
	tempPoint.y = object->m_Rect.bottom / m_TileSize;

	// 충돌
	for (int i = 0; i < object->m_CheckCountX; i++) {
		tempRect.left = tempPoint.x * m_TileSize;
		tempRect.top = tempPoint.y * m_TileSize;
		tempRect.right = (tempPoint.x + 1) * m_TileSize;
		tempRect.bottom = (tempPoint.y + 1) * m_TileSize;

		if (m_MapCollMap[tempPoint.y][tempPoint.x] != 0 && m_MapCollMap[tempPoint.y][tempPoint.x] != 7) {
			if (IntersectRect(&tempCollRect, &tempRect, &object->m_Rect)) {
				Log("아래 충돌!!");
				object->m_PosY -= object->m_Rect.bottom - tempPoint.y * m_TileSize;
				object->UpdateRect();
				return 1;
			}
			else if ((tempPoint.y * m_TileSize) == object->m_Rect.bottom) {
				//Log("아래 라인!!");
				if (object->m_ObjectType == 0) {
					if (m_MapCollMap[tempPoint.y][tempPoint.x] == 6) {
						if (m_MapCollMap[tempPoint.y][tempPoint.x + 1] == 6) {
							if (object->m_Rect.left > tempRect.left && object->m_Rect.right > tempRect.right) {
								//if (dynamic_cast<Player*>(object)->m_Dir == Direction::DOWN && object->m_Speed == 0) {
								if (GetAsyncKeyState(VK_DOWN) && object->m_Speed == 0) {
									GameManager::GetGameManager()->GetSceneManager()->ChangeScene("PlayBonusScene");
									GameManager::GetGameManager()->GetSceneManager()->DestroyScene("PlayScene");
								}
							}
						}
					}
				}
				return 2;
			}
		}
		else if (m_MapCollMap[tempPoint.y][tempPoint.x] == 7 && object->m_ObjectType == 0) {
			if (IntersectRect(&tempCollRect, &tempRect, &object->m_Rect)) {
				m_Map[tempPoint.y][tempPoint.x] = 28;
				m_MapCollMap[tempPoint.y][tempPoint.x] = 0;
				return 7;
			}
		}
	}
	tempPoint.x++;

	if (object->m_Rect.right > tempPoint.x * m_TileSize) {
		if (m_MapCollMap[tempPoint.y][tempPoint.x] != 0 && m_MapCollMap[tempPoint.y][tempPoint.x] != 7) {
			if (IntersectRect(&tempCollRect, &tempRect, &object->m_Rect)) {
				Log("아래 충돌!!");
				object->m_PosY -= object->m_Rect.bottom - tempPoint.y * m_TileSize;
				object->UpdateRect();
				return 1;
			}
			else if ((tempPoint.y * m_TileSize) == object->m_Rect.bottom) {
				//Log("아래 라인!!");
				return 2;
			}
		}
		else if (m_MapCollMap[tempPoint.y][tempPoint.x] == 7 && object->m_ObjectType == 0) {
			if (IntersectRect(&tempCollRect, &tempRect, &object->m_Rect)) {
				m_Map[tempPoint.y][tempPoint.x] = 28;
				m_MapCollMap[tempPoint.y][tempPoint.x] = 0;
				return 7;
			}
		}
	}
	return 0;
}

int SecondScene::CheckCollisionLeft(Object * object)
{
	POINT tempPoint;
	RECT tempRect;
	RECT tempCollRect;

	tempPoint.x = object->m_Rect.left / m_TileSize;
	tempPoint.y = object->m_Rect.top / m_TileSize;

	for (int i = 0; i < object->m_CheckCountY; i++) {
		tempRect.left = tempPoint.x * m_TileSize;
		tempRect.top = tempPoint.y * m_TileSize;
		tempRect.right = (tempPoint.x + 1) * m_TileSize;
		tempRect.bottom = (tempPoint.y + 1) * m_TileSize;

		if (m_MapCollMap[tempPoint.y][tempPoint.x] != 0 && m_MapCollMap[tempPoint.y][tempPoint.x] != 7) {
			if (IntersectRect(&tempCollRect, &tempRect, &object->m_Rect)) {
				Log("왼쪽 충돌1!!");
				switch (object->m_ObjectType)
				{
				case 0:case 1: case 2:
					object->m_PosX += (tempPoint.x + 1) * m_TileSize - object->m_Rect.left;
					object->UpdateRect();
					return 1;
				case 3:
					return 1;
				}
			}
		}
		if (m_MapCollMap[tempPoint.y][tempPoint.x - 1] != 0 && m_MapCollMap[tempPoint.y][tempPoint.x - 1] != 7) {
			if ((tempPoint.x * m_TileSize) == object->m_Rect.left) {
				//Log("왼쪽 라인!!");
				return 2;
			}
		}
		else if (m_MapCollMap[tempPoint.y][tempPoint.x] == 7 && object->m_ObjectType == 0) {
			if (IntersectRect(&tempCollRect, &tempRect, &object->m_Rect)) {
				m_Map[tempPoint.y][tempPoint.x] = 28;
				m_MapCollMap[tempPoint.y][tempPoint.x] = 0;
				return 7;
			}
		}
		tempPoint.y++;
	}

	tempRect.left = tempPoint.x * m_TileSize;
	tempRect.top = tempPoint.y * m_TileSize;
	tempRect.right = (tempPoint.x + 1) * m_TileSize;
	tempRect.bottom = (tempPoint.y + 1) * m_TileSize;

	if (object->m_Rect.bottom > tempPoint.y * m_TileSize) {
		if (m_MapCollMap[tempPoint.y][tempPoint.x] != 0 && m_MapCollMap[tempPoint.y][tempPoint.x] != 7) {
			if (IntersectRect(&tempCollRect, &tempRect, &object->m_Rect)) {
				Log("왼쪽 충돌2!!");
				switch (object->m_ObjectType)
				{
				case 0:case 1: case 2:
					object->m_PosX += (tempPoint.x + 1) * m_TileSize - object->m_Rect.left;
					object->UpdateRect();
					return 1;
				case 3:
					return 1;
				}
			}
		}
		if (m_MapCollMap[tempPoint.y][tempPoint.x - 1] != 0 && m_MapCollMap[tempPoint.y][tempPoint.x - 1] != 7) {
			if ((tempPoint.x * m_TileSize) == object->m_Rect.left) {
				//Log("왼쪽 라인!!");
				return 2;
			}
		}
		else if (m_MapCollMap[tempPoint.y][tempPoint.x] == 7 && object->m_ObjectType == 0) {
			if (IntersectRect(&tempCollRect, &tempRect, &object->m_Rect)) {
				m_Map[tempPoint.y][tempPoint.x] = 28;
				m_MapCollMap[tempPoint.y][tempPoint.x] = 0;
				return 7;
			}
		}
	}
	return 0;
}

int SecondScene::CheckCollisionRight(Object * object)
{
	POINT tempPoint;
	RECT tempRect;
	RECT tempCollRect;

	tempPoint.x = object->m_Rect.right / m_TileSize;
	tempPoint.y = object->m_Rect.top / m_TileSize;

	for (int i = 0; i < object->m_CheckCountY; i++) {
		tempRect.left = tempPoint.x * m_TileSize;
		tempRect.top = tempPoint.y * m_TileSize;
		tempRect.right = (tempPoint.x + 1) * m_TileSize;
		tempRect.bottom = (tempPoint.y + 1) * m_TileSize;

		if (m_MapCollMap[tempPoint.y][tempPoint.x] != 0 && m_MapCollMap[tempPoint.y][tempPoint.x] != 7) {
			if (IntersectRect(&tempCollRect, &tempRect, &object->m_Rect)) {
				Log("오른쪽 충돌!!");
				switch (object->m_ObjectType)
				{
				case 0:case 1: case 2:
					object->m_PosX -= object->m_Rect.right - (tempPoint.x * m_TileSize);
					object->UpdateRect();
					return 1;
				case 3:
					return 1;
				}
			}
			else if ((tempPoint.x * m_TileSize) == object->m_Rect.right) {
				//Log("오른쪽 라인!!");
				/*if (object->m_ObjectType == 0) {
				if (m_MapCollMap[tempPoint.y][tempPoint.x] == 6) {
				if (dynamic_cast<Player*>(object)->m_Dir == Direction::RIGHT) {
				GameManager::GetGameManager()->GetSceneManager()->ChangeScene("PlayBonusScene");
				GameManager::GetGameManager()->GetSceneManager()->DestroyScene("PlayScene");
				}
				}
				}*/
				return 2;
			}
		}
		else if (m_MapCollMap[tempPoint.y][tempPoint.x] == 7 && object->m_ObjectType == 0) {
			if (IntersectRect(&tempCollRect, &tempRect, &object->m_Rect)) {
				m_Map[tempPoint.y][tempPoint.x] = 28;
				m_MapCollMap[tempPoint.y][tempPoint.x] = 0;
				return 7;
			}
		}
		tempPoint.y++;
	}

	tempRect.left = tempPoint.x * m_TileSize;
	tempRect.top = tempPoint.y * m_TileSize;
	tempRect.right = (tempPoint.x + 1) * m_TileSize;
	tempRect.bottom = (tempPoint.y + 1) * m_TileSize;

	if (object->m_Rect.bottom > tempPoint.y * m_TileSize) {
		if (m_MapCollMap[tempPoint.y][tempPoint.x] != 0 && m_MapCollMap[tempPoint.y][tempPoint.x] != 7) {
			if (IntersectRect(&tempCollRect, &tempRect, &object->m_Rect)) {
				Log("오른쪽 충돌!!");
				switch (object->m_ObjectType)
				{
				case 0:case 1: case 2:
					object->m_PosX -= object->m_Rect.right - (tempPoint.x * m_TileSize);
					object->UpdateRect();
					return 1;
				case 3:
					return 1;
				}
			}
			else if ((tempPoint.x * m_TileSize) == object->m_Rect.right) {
				//Log("오른쪽 라인!!");
				return 2;
			}
		}
		else if (m_MapCollMap[tempPoint.y][tempPoint.x] == 7 && object->m_ObjectType == 0) {
			if (IntersectRect(&tempCollRect, &tempRect, &object->m_Rect)) {
				m_Map[tempPoint.y][tempPoint.x] = 28;
				m_MapCollMap[tempPoint.y][tempPoint.x] = 0;
				return 7;
			}
		}
	}

	return 0;
}

void SecondScene::CollisionTop(Object * object)
{
	object->m_Gravity = 0;
	object->m_DirTopBottom = 0;
}

void SecondScene::CollisionBottom(Object * object)
{
	object->m_state = 0;
	object->m_Gravity = 0;
	object->m_canBottom = false;

	if (object->m_ItemType == 2) {
		object->m_Gravity = 8.0f;
	}
	else if (object->m_ObjectType == 0) {
		switch (object->m_CharLevel)
		{
		case 0:
			if (object->m_Speed == 0) {
				switch (object->m_DirLeftRight)
				{
				case 0:
					object->SetSprite(21, 2, 21, 21, 100);
					break;
				case 1:
					object->SetSprite(20, 2, 20, 20, 100);
					break;
				}
			}
			else {
				switch (object->m_DirLeftRight)
				{
				case 0:
					object->SetSprite(22, 2, 22, 24, 100);
					break;
				case 1:
					object->SetSprite(17, 2, 17, 19, 100);
					break;
				}
			}
			break;
		case 1:
			if (object->m_Speed == 0) {
				switch (object->m_DirLeftRight)
				{
				case 0:
					object->SetSprite(21, 0, 21, 21, 100);
					break;
				case 1:
					object->SetSprite(20, 0, 20, 20, 100);
					break;
				}
			}
			else {
				switch (object->m_DirLeftRight)
				{
				case 0:
					object->SetSprite(22, 0, 22, 24, 100);
					break;
				case 1:
					object->SetSprite(17, 0, 17, 19, 100);
					break;
				}
			}
			break;
		case 2:
			if (object->m_Speed == 0) {
				switch (object->m_DirLeftRight)
				{
				case 0:
					object->SetSprite(21, 3, 21, 21, 100);
					break;
				case 1:
					object->SetSprite(20, 3, 20, 20, 100);
					break;
				}
			}
			else {
				switch (object->m_DirLeftRight)
				{
				case 0:
					object->SetSprite(22, 3, 22, 24, 100);
					break;
				case 1:
					object->SetSprite(17, 3, 17, 19, 100);
					break;
				}
			}
			break;
		}
	}
}

void SecondScene::CollisionLeft(Object * object)
{
	switch (object->m_ObjectType)
	{
	case 0:
		object->m_Speed = object->m_MinSpeed;
		object->m_canLeft = false;
		break;
	case 1:
		object->m_DirLeftRight = 0;
		object->CollUpdate(object->m_DirLeftRight);
		break;
	case 2:
		switch (object->m_MonsterType)
		{
		case 1:
			break;
		case 2:
			switch (object->m_CharLevel)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:

				break;
			}
			break;
		}
		break;
	}
}

void SecondScene::CollisionRight(Object * object)
{
	switch (object->m_ObjectType)
	{
	case 0:
		object->m_Speed = object->m_MinSpeed;
		object->m_canRight = false;
		break;
	case 1:
		object->m_DirLeftRight = 1;
		object->CollUpdate(object->m_DirLeftRight);
		break;
	case 2:
		break;
	}
}

void SecondScene::NoCollisionTop(Object * object)
{

}

void SecondScene::NoCollisionBottom(Object * object)
{
	if (!object->m_state) object->m_state = true;
}

void SecondScene::NoCollisionLeft(Object * object)
{
	object->m_canLeft = true;
}

void SecondScene::NoCollisionRight(Object * object)
{
	object->m_canRight = true;
}

bool SecondScene::CheckCollisionObject(Object * object, list<Object*>* objectList)
{
	RECT tempRect;
	iter = objectList->begin();
	for (; iter != objectList->end(); iter++) {
		// 플레이어와 몬스터의 충돌
		if ((*iter)->m_ObjectType == 1 && (*iter)->m_UseCollision) {
			if (IntersectRect(&tempRect, &object->m_Rect, &(*iter)->m_Rect)) {
				// 플레이어가 몬스터를 위에서 공격
				if (object->m_state == 1 && object->m_Gravity < 0 && object->m_Rect.bottom >(*iter)->m_Rect.top) {
					switch ((*iter)->m_MonsterType)
					{
					case 1:	// 몬스터 1 - 버섯 몬스터
						CharacterManager::GetPlayer()->m_totalScore += 200;
						switch ((*iter)->m_CharLevel)
						{
						case 1:
							dynamic_cast<Monster*>(*iter)->DieMotion(0);
							break;
						}
						/*delete *iter;
						objectList->erase(iter);*/
						object->m_Gravity = 10.0f;
						break;
					case 2:	// 몬스터 2 - 거북이 몬스터
						switch ((*iter)->m_CharLevel)
						{
						case 1:
							CharacterManager::GetPlayer()->m_totalScore += 500;
							if ((*iter)->m_Speed == 0) {
								if ((*iter)->m_PosX > object->m_PosX)	(*iter)->m_DirLeftRight = 0;
								else									(*iter)->m_DirLeftRight = 1;
								(*iter)->SetCollInit((*iter)->m_Width, (*iter)->m_Height, (*iter)->m_UseCollision, 7.0f);
							}
							else {
								(*iter)->SetCollInit((*iter)->m_Width, (*iter)->m_Height, (*iter)->m_UseCollision, 0);
							}
							break;
						case 2:
							CharacterManager::GetPlayer()->m_totalScore += 200;
							(*iter)->SetSprite(13, 0, 13, 13, 100);
							(*iter)->SetCollInit(32, 36, true, 0);
							(*iter)->SetImgSizeInit(16, 15);
							(*iter)->m_CharLevel = 1;
							break;
						}
						object->m_Gravity = 10.0f;
						break;
					}

					return true;
				}

				if ((*iter)->m_MonsterType == 2 && (*iter)->m_CharLevel == 1) {
					// 거북이가 움직이지 않을때
					if ((*iter)->m_Speed == 0) {
						CharacterManager::GetPlayer()->m_totalScore += 500;
						(*iter)->SetSprite(13, 0, 13, 13, 100);
						(*iter)->SetCollInit((*iter)->m_Width, (*iter)->m_Height, true, 7.0f);
						(*iter)->m_DirLeftRight = object->m_DirLeftRight;
						switch ((*iter)->m_DirLeftRight)
						{
						case 0:
							(*iter)->m_PosX += object->m_Rect.right - (*iter)->m_Rect.left;
							break;
						case 1:
							(*iter)->m_PosX -= (*iter)->m_Rect.right - object->m_Rect.left;
							break;
						}
					}
					// 거북이가 움직이고 있을때
					else {
						CharacterManager::GetPlayer()->m_totalScore += 500;
						object->CollMonster(object->m_CharLevel, (*iter)->m_ItemType);
					}
				}
				// 플레이어와 몬스터간의 좌우 충돌
				else {
					if ((*iter)->m_DirLeftRight == 0) {
						(*iter)->m_DirLeftRight = 1;
						(*iter)->CollUpdate((*iter)->m_DirLeftRight);
					}
					else if ((*iter)->m_DirLeftRight == 1) {
						(*iter)->m_DirLeftRight = 0;
						(*iter)->CollUpdate((*iter)->m_DirLeftRight);
					}
					object->CollMonster(object->m_CharLevel, (*iter)->m_ItemType);
				}
				return true;
			}
		}
		// 플레이어와 아이템의 충돌
		else if ((*iter)->m_ObjectType == 2) {
			if ((*iter)->m_UseCollision) {
				if (IntersectRect(&tempRect, &object->m_Rect, &(*iter)->m_Rect)) {
					object->EatItem(object->m_CharLevel, (*iter)->m_ItemType);
					delete *iter;
					objectList->erase(iter);
					return true;
				}
			}
			else if ((*iter)->m_PosY > 800) {
				delete *iter;
				objectList->erase(iter);
				return true;
			}
			else if ((*iter)->m_wallBreakDir == 5) {
				if ((*iter)->m_count == 5) {
					delete *iter;
					objectList->erase(iter);
					return true;
				}
				(*iter)->m_count++;
			}
			else if ((*iter)->m_ItemType == 1 && (*iter)->m_state == 1) {
				delete *iter;
				objectList->erase(iter);
				return true;
			}
		}
	}
	return false;
}

bool SecondScene::CheckCollisionObject(list<Object*>* objectList)
{
	RECT temp;

	iter = objectList->begin();

	if (objectList->size() > 1) {
		for (; iter != objectList->end(); iter++) {
			iter2 = iter;
			iter2++;
			for (; iter2 != objectList->end(); iter2++) {
				if (IntersectRect(&temp, &(*iter)->m_Rect, &(*iter2)->m_Rect)) {
					if ((*iter)->m_CharLevel == 1 && (*iter)->m_MonsterType == 2) {
						switch ((*iter2)->m_MonsterType)
						{
						case 1:
							dynamic_cast<Monster*>(*iter2)->DieMotion(1);
							break;
						case 2:
							dynamic_cast<Monster2*>(*iter2)->DieMotion(1);
							break;
						}
					}
					else if ((*iter2)->m_CharLevel == 1 && (*iter2)->m_MonsterType == 2) {
						switch ((*iter)->m_MonsterType)
						{
						case 1:
							dynamic_cast<Monster*>(*iter)->DieMotion(1);
							break;
						case 2:
							dynamic_cast<Monster2*>(*iter)->DieMotion(1);
							break;
						}
					}
					else {
						if ((*iter)->m_DirLeftRight == 0) {
							(*iter)->m_DirLeftRight = 1;
							(*iter)->CollUpdate((*iter)->m_DirLeftRight);
						}
						else if ((*iter)->m_DirLeftRight == 1) {
							(*iter)->m_DirLeftRight = 0;
							(*iter)->CollUpdate((*iter)->m_DirLeftRight);
						}

						if ((*iter2)->m_DirLeftRight == 0) {
							(*iter2)->m_DirLeftRight = 1;
							(*iter2)->CollUpdate((*iter2)->m_DirLeftRight);
						}
						else if ((*iter2)->m_DirLeftRight == 1) {
							(*iter2)->m_DirLeftRight = 0;
							(*iter2)->CollUpdate((*iter2)->m_DirLeftRight);
						}
					}
				}
			}
		}
	}
	return false;
}

bool SecondScene::CheckCollisionObject(list<Object*>* objectList, list<Object*>* objectList2)
{
	RECT tempRect;
	iter = objectList->begin();
	iter2 = objectList2->begin();

	for (; iter != objectList->end(); iter++) {
		for (; iter2 != objectList2->end(); iter2++) {
			if ((*iter)->m_UseCollision == true && (*iter2)->m_UseCollision == true) {
				if (IntersectRect(&tempRect, &(*iter)->m_Rect, &(*iter2)->m_Rect)) {
					CharacterManager::GetPlayer()->m_totalScore += 200;
					(*iter)->m_DirLeftRight = (*iter2)->m_DirLeftRight;
					switch ((*iter)->m_MonsterType)
					{
					case 1:
						dynamic_cast<Monster*>(*iter)->DieMotion(1);
						break;
					case 2:
						dynamic_cast<Monster2*>(*iter)->DieMotion(1);
						break;
					}

					/*delete *iter;
					objectList->erase(iter);*/

					(*iter2)->m_chkColl = true;
					(*iter2)->SetSprite(7, 9, 9, 11, 200);
					(*iter2)->SetCollInit(36, 36, false, 0);
					(*iter2)->SetImgSizeInit(16, 16);
					return true;
				}
			}
		}
	}
	return false;
}
