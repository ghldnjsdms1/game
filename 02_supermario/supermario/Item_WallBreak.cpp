#include "Item_WallBreak.h"
#include "CharacterManager.h"


Item_WallBreak::Item_WallBreak()
{
	Init();
}


Item_WallBreak::~Item_WallBreak()
{
}

void Item_WallBreak::Init()
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
	m_PosX = 700;
	m_PosY = 50;
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
	m_SpriteTime = 200; // 0.1초
	m_SpriteXIndex = 4;
	m_SpriteYIndex = 0;
	m_SpriteStartIndex = 0;
	m_SpriteEndIndex = 0;
	m_SpriteX = false;
	m_SpriteY = false;

	m_DirTopBottom = 0;
	m_DirLeftRight = 0;

	m_count = 0;
	m_state = 0;
	m_Gravity = 0.0f;
	m_Speed = 2.0f;				// 움직일 때 사용될 속도
	m_MaxSpeed = 6.0f;
	m_canLeft = true;
	m_canRight = false;

	m_ObjectType = 2;
	m_UseCollision = false;

	m_secure = false;

	m_dwTime = GetTickCount();
}

void Item_WallBreak::Update()
{
	MoveUpdate();

	Scroll();

	UpdateRect();

	BaseUpdate();
}

void Item_WallBreak::Render(HDC memDC, HDC backMemDC)
{
	BaseRender(memDC, backMemDC);
}

void Item_WallBreak::Direct(int dir)
{
	switch (m_wallBreakDir)
	{
	case 5:
		m_Speed = 0.0f;
		m_Gravity = 0.0f;
		m_SpriteYIndex = 0;
		break;
	case 1:
		m_Speed = -2.0f;
		m_Gravity = 30.0f;
		m_SpriteYIndex = 2;
		break;
	case 2:
		m_Speed = 2.0f;
		m_Gravity = 30.0f;
		m_SpriteYIndex = 1;
		break;
	case 3:
		m_Speed = 2.0f;
		m_Gravity = 15.0f;
		m_SpriteYIndex = 2;
		break;
	case 4:
		m_Speed = -2.0f;
		m_Gravity = 15.0f;
		m_SpriteYIndex = 1;
		break;
	}
}

void Item_WallBreak::Scroll()
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

void Item_WallBreak::MoveUpdate()
{
	switch (m_wallBreakDir)
	{
	case 5:
		m_Speed = 0.0f;
		m_Gravity = 0.0f;
		break;
	case 1:
		m_PosX += m_Speed;
		m_PosY -= m_Gravity;
		m_Gravity--;
		break;
	case 2:
		m_PosX += m_Speed;
		m_PosY -= m_Gravity;
		m_Gravity--;
		break;
	case 3:
		m_PosX += m_Speed;
		m_PosY -= m_Gravity;
		m_Gravity--;
		break;
	case 4:
		m_PosX += m_Speed;
		m_PosY -= m_Gravity;
		m_Gravity--;
		break;
	}
}
