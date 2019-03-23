#include "Item_Coin.h"
#include "CharacterManager.h"


Item_Coin::Item_Coin()
{
	Init();
}


Item_Coin::~Item_Coin()
{
}

void Item_Coin::Init()
{
	// 처음 초기화를 해야할 것들

	// 해당 오브젝트의 활성화
	SetActive(true);

	// 오브젝트 위에 그려질 사각형활성화
	SetShowRect(false);

	// 사각형을 그린다면 타이틀만 그릴 것인지 설정
	SetDrawOnlyTitle(true);

	// 오브젝트 이미지 그리기 활성화
	SetShowImage(true);

	// BMP 이미지 가져오기
	LoadImg(L"mario_item.bmp", 0, 0);

	// 이미지에 투명색을 사용할 것인지 설정
	m_UseTrasparent = true;

	// 숨길 색상을 지접합니다.
	TransparentColor = RGB(255, 246, 0);
	//RGB(0, 0, 0);

	// 스프라이트 이미지를 사용할 것인지 설정
	m_UseSprite = true;

	// 플레이어의 초기 좌표를 설정
	//m_PosX = CharacterManager::GetPlayer()->m_PosX + 600;
	m_PosX = 0;
	m_PosY = 0;
	//m_PosY = 542;

	// 현재 몬스터의 가로, 세로 크기 (그려질 크기)
	m_Width = 36;
	m_Height = 36;

	// RECT값 동기화
	UpdateRect();

	// 몬스터 이미지 크기
	m_ImgWidth = 16;
	m_ImgHeight = 16;

	m_CheckCountX = m_Width / MAP_TILE_SIZE;
	m_CheckCountY = m_Height / MAP_TILE_SIZE;

	// 스프라이트 정보를 초기화합니다.
	m_SpriteTime = 100; // 0.1초
	m_SpriteXIndex = 0;
	m_SpriteYIndex = 6;
	m_SpriteStartIndex = 0;
	m_SpriteEndIndex = 3;
	m_SpriteX = true;
	m_SpriteY = false;

	m_DirTopBottom = 0;
	m_DirLeftRight = 0;

	m_count = 0;
	m_state = 0;
	m_Gravity = 15.0f;
	m_Speed = 2.0f;				// 움직일 때 사용될 속도
	m_MaxSpeed = 6.0f;
	m_canLeft = true;
	m_canRight = false;

	m_ObjectType = 2;
	m_UseCollision = false;
	m_ItemType = 1;

	m_secure = false;

	m_dwTime = GetTickCount();
}

void Item_Coin::Update()
{
	MoveUpdate();

	Scroll();

	UpdateRect();

	BaseUpdate();
}

void Item_Coin::Render(HDC memDC, HDC backMemDC)
{
	BaseRender(memDC, backMemDC);
}

void Item_Coin::Scroll()
{
	m_Scroll = CharacterManager::GetPlayer()->GetScroll();
	/*if (CharacterManager::GetPlayer()->m_PosX < 200) {
		m_Scroll.x = m_passScroll.x;
	}
	else if (CharacterManager::GetPlayer()->m_PosX - 200 >= m_passScroll.x) {
		m_passScroll.x = CharacterManager::GetPlayer()->m_PosX - 200;
		m_Scroll.x = m_passScroll.x;
	}
	else {
		m_Scroll.x = m_passScroll.x;
	}*/
}

void Item_Coin::MoveUpdate()
{
	if (!m_UseCollision) {
		if (m_Gravity > -12) {
			m_PosY -= m_Gravity;
			m_Gravity--;
		}
		else {
			m_state = 1;
		}
	}
}
