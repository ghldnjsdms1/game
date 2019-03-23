#include "Monster2.h"
#include "CharacterManager.h"


Monster2::Monster2()
{
	this->Init();
}


Monster2::~Monster2()
{
	//if (m_Image != NULL) DeleteObject(m_Image);
}

void Monster2::Init()
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
	LoadImg(L"mario_monster.bmp", 0, 0);

	// 이미지에 투명색을 사용할 것인지 설정
	m_UseTrasparent = true;

	// 숨길 색상을 지접합니다.
	TransparentColor = RGB(255, 246, 0);
	//RGB(0, 0, 0);

	// 스프라이트 이미지를 사용할 것인지 설정
	m_UseSprite = true;

	// 플레이어의 초기 좌표를 설정
	//m_PosX = CharacterManager::GetPlayer()->m_PosX + 600;
	m_PosX = 500;
	m_PosY = 300;
	//m_PosY = 542;

	// 현재 몬스터의 가로, 세로 크기 (그려질 크기)
	m_Width = 32;
	m_Height = 48;

	// RECT값 동기화
	UpdateRect();

	// 몬스터 이미지 크기
	m_ImgWidth = 16;
	m_ImgHeight = 24;

	m_CheckCountX = m_Width / MAP_TILE_SIZE;
	m_CheckCountY = m_Height / MAP_TILE_SIZE;

	// 스프라이트 정보를 초기화합니다.
	m_SpriteTime = 200; // 0.1초
	m_SpriteXIndex = 6;
	m_SpriteYIndex = 0;
	m_SpriteStartIndex = 6;
	m_SpriteEndIndex = 7;
	m_SpriteX = true;
	m_SpriteY = false;

	m_DirTopBottom = 0;
	m_DirLeftRight = 1;

	m_count = 0;
	m_state = 0;
	m_Gravity = 0.0f;
	m_Speed = 2.0f;				// 움직일 때 사용될 속도
	m_MaxSpeed = 6.0f;
	m_canLeft = false;
	m_canRight = true;

	m_CharLevel = 2;
	m_ObjectType = 1;
	m_MonsterType = 2;
	m_UseCollision = true;

	m_secure = false;

	m_dwTime = GetTickCount();
}

void Monster2::Update()
{
	MoveUpdate();

	Scroll();

	UpdateRect();

	BaseUpdate();
}

void Monster2::Render(HDC memDC, HDC backMemDC)
{
	//BaseRender(memDC, backMemDC);

	// 오브젝트가 활성화중이라면
	if (GetActive()) {
		// 사각형만 그리고 && 타이틀만 출력하는 것이라면
		if (GetShowRect() && GetDrawOnlyTitle()) {
			Rectangle(backMemDC, m_Rect.left - m_Scroll.x, m_Rect.top, m_Rect.right - m_Scroll.x, m_Rect.bottom);
		}

		// 이미지를 띄우도록 설정했다면
		if (GetShowImage() && !ImageNullCheck()) {

			SelectObject(memDC, m_Image);

			// 스프라이트를 사용중이라면
			if (m_UseSprite) {
				TransparentBlt(
					backMemDC,
					m_Rect.left - m_Scroll.x, m_Rect.top, m_Width, m_Height,
					memDC,
					(m_SpriteXIndex * (m_ImgWidth + 14)),
					m_SpriteYIndex * m_ImgHeight,
					m_ImgWidth, m_ImgHeight,
					// 투명색을 사용중이라면 TransparentColor를, 아니라면 NULL을 넣어서 투명색을 사용하지 않도록 설정
					(m_UseTrasparent) ? TransparentColor : NULL);
			}
			// 스프라이트를 사용중이 아니라면
			else {
				TransparentBlt(
					backMemDC,
					m_Rect.left, m_Rect.top, m_Width, m_Height,
					memDC,
					0, 0, m_ImgWidth, m_ImgHeight,
					// 투명색을 사용중이라면 TransparentColor를, 아니라면 NULL을 넣어서 투명색을 사용하지 않도록 설정
					(m_UseTrasparent) ? TransparentColor : NULL);
			}

		}
		// 사각형을 그리고 && 타이틀만 출력하는것이 아니라면
		if (GetShowRect() && !GetDrawOnlyTitle()) {
			// 검은색으로 사각형을 칠합니다.
			FillRect(backMemDC, &m_Rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
	}
}

//void Monster2::UpdateRect()
//{
//	m_Rect = {
//		m_PosX - (m_Width / 2),
//		m_PosY - (m_Height / 24),
//		m_PosX + (m_Width / 2),
//		m_PosY + (m_Height / 2) };
//}

void Monster2::Scroll()
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

void Monster2::SetPos(int x, int y)
{
	m_PosX = x + 600;
	m_PosY = 50;
}

void Monster2::MoveUpdate()
{
	// 왼쪽
	if (m_DirLeftRight == 1 && m_dwTime > 2000) {
		m_PosX -= m_Speed;
	}
	// 오른쪽
	else if (m_DirLeftRight == 0 && m_dwTime > 2000) {
		m_PosX += m_Speed;
	}
	m_dwTime = GetTickCount();

	if (m_Gravity > -40 && m_state == 1) {
		m_PosY -= m_Gravity;
		m_Gravity -= 1.0f;

		if (m_Gravity <= 0) {
			m_colDirTB = COL_BOTTOM;
		}
		else {
			m_colDirTB = COL_TOP;
		}
	}
	if (m_state == 0) {
		m_colDirTB = COL_NONE;
	}
}

void Monster2::CollUpdate(int dir)
{
	if (m_MonsterType == 2 && m_CharLevel != 1) {
		if (dir == 1) {
			SetSprite(6, 0, 6, 7, m_SpriteTime);
		}
		else {
			SetSprite(8, 0, 8, 9, m_SpriteTime);
		}
	}
}

void Monster2::DieMotion(int type)
{
	switch (type)
	{
	case 0:
		break;
	case 1:
		SetSprite(14, 0, 14, 14, 500);
		SetCollInit(m_Width, m_Height, false, m_Speed);
		break;
	}

	m_chkColl = true;
	m_CharLevel = 0;
	m_dieTime = GetTickCount();

	m_Gravity = 10.0f;
	m_state = 1;
}
