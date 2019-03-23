#include "GameOverScene.h"
#include "GameManager.h"


GameOverScene::GameOverScene()
{
	//Init();
}


GameOverScene::~GameOverScene()
{
	//Destroy();
}

void GameOverScene::Init()
{
	Log("gameover");
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

	m_imgSize.x = 256;
	m_imgSize.y = 224;

	// 타일맵 불러오기
	LoadMap();

	m_SpriteTime = 200; // 0.2초
	m_SpriteXIndex = 0;
	m_SpriteYIndex = 0;
	m_SpriteStartIndex = 0;
	m_SpriteEndIndex = 0;

	m_Image = ImageLoad(L"gameover.bmp", 0, 0);

	if (m_Image == NULL) {
		Log("이미지 불러오기 실패!");
	}
	m_dwTime = GetTickCount();
	m_count = 0;
}

void GameOverScene::Update()
{
	if (CharacterManager::GetPlayer()->m_currentScene != SCENE_GAMEOVER) {
		//CharacterManager::GetPlayer()->m_currentScene = SCENE_GAMEOVER;
		/*m_pPlayer->SetPos(m_charPos.x, m_charPos.y);
		m_pPlayer->UpdateRect();*/
	}
	
	if (CharacterManager::GetPlayer()->m_life <= 0) {
		Log("!!!!!!!!!!!!!!!!");
		GameManager::GetGameManager()->GetSceneManager()->ChangeScene("MainScene");
		Log("#############");
		GameManager::GetGameManager()->GetSceneManager()->DestroyScene("GameOverScene");
		Log("@@@@@@@@@@@@");
	}

	switch (m_count)
	{
	case 0:
		m_dwTime = GetTickCount();
		m_count++;
		if (CharacterManager::GetPlayer()->m_CharLevel == -1) {
			m_SpriteXIndex = 1;
			m_SpriteYIndex = 0;
			m_SpriteStartIndex = 1;
			m_SpriteEndIndex = 1;
		}
		else {
			m_SpriteXIndex = 0;
			m_SpriteYIndex = 0;
			m_SpriteStartIndex = 0;
			m_SpriteEndIndex = 0;
		}
		break;
	case 1:
		if (GetTickCount() - m_dwTime > 3000) {
			m_count--;
			switch (CharacterManager::GetPlayer()->m_CharLevel)
			{
			case -1:
				if (CharacterManager::GetPlayer()->m_currentScene == SCENE_PLAY) {
					GameManager::GetGameManager()->GetSceneManager()->ChangeScene("PlayScene");
					GameManager::GetGameManager()->GetSceneManager()->DestroyScene("GameOverScene");
					CharacterManager::GetPlayer()->SceneInit(SCENE_PLAY, 105, 462, true, 0, false);
					CharacterManager::GetPlayer()->ScrollInit(0, 0);
				}
				else if (CharacterManager::GetPlayer()->m_currentScene == SCENE_SECOND) {
					GameManager::GetGameManager()->GetSceneManager()->ChangeScene("SecondScene");
					GameManager::GetGameManager()->GetSceneManager()->DestroyScene("GameOverScene");
					CharacterManager::GetPlayer()->SceneInit(SCENE_SECOND, 105, 462, true, 0, false);
					CharacterManager::GetPlayer()->ScrollInit(0, 0);
				}
				break;
			case 0:
				if (CharacterManager::GetPlayer()->m_currentScene == SCENE_PLAY) {
					GameManager::GetGameManager()->GetSceneManager()->ChangeScene("SecondScene");
					GameManager::GetGameManager()->GetSceneManager()->DestroyScene("GameOverScene");
					CharacterManager::GetPlayer()->SceneInit(SCENE_SECOND, 105, 462, true, CharacterManager::GetPlayer()->m_CharLevel, false);
					CharacterManager::GetPlayer()->ScrollInit(0, 0);
					CharacterManager::GetPlayer()->SetTime(400);
				}
				break;
			case 1: case 2:
				if (CharacterManager::GetPlayer()->m_currentScene == SCENE_PLAY) {
					GameManager::GetGameManager()->GetSceneManager()->ChangeScene("SecondScene");
					GameManager::GetGameManager()->GetSceneManager()->DestroyScene("GameOverScene");
					CharacterManager::GetPlayer()->SceneInit(SCENE_SECOND, 105, 444, true, CharacterManager::GetPlayer()->m_CharLevel, false);
					CharacterManager::GetPlayer()->ScrollInit(0, 0);
					CharacterManager::GetPlayer()->SetTime(400);
				}
				break;
				break;
			}
		}
		break;
	}
}

void GameOverScene::Render(HDC memDC, HDC backMemDC)
{
	FillRect(backMemDC, &m_FillRect, (HBRUSH)GetStockObject(BLACK_BRUSH));

	SelectObject(memDC, m_Image);

	TransparentBlt(
		backMemDC,
		0, 0,
		MAIN_WND_WIDTH, MAIN_WND_HEIGHT,
		memDC,
		m_imgSize.x * m_SpriteXIndex, m_imgSize.y * m_SpriteYIndex,
		m_imgSize.x, m_imgSize.y,
		NULL);
}

void GameOverScene::Destroy()
{
}

HBITMAP GameOverScene::ImageLoad(LPCWSTR path, int width, int height)
{
	return (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
}

void GameOverScene::LoadImg(LPCWSTR path, int width, int height)
{
}

void GameOverScene::InitMapData()
{
}

void GameOverScene::LoadMap()
{
}

void GameOverScene::SaveMap()
{
}
