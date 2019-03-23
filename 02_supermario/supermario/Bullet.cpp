#include "Bullet.h"
#include "CharacterManager.h"


Bullet::Bullet()
{
	Init();
}


Bullet::~Bullet()
{
}

void Bullet::Init()
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
	//TransparentColor = NULL;
	//RGB(0, 0, 0);

	// 스프라이트 이미지를 사용할 것인지 설정
	m_UseSprite = true;

	// 플레이어의 초기 좌표를 설정
	m_PosX = 0;
	m_PosY = 0;

	// 현재 몬스터의 가로, 세로 크기 (그려질 크기)
	m_Width = 18;
	m_Height = 18;

	// RECT값 동기화
	UpdateRect();

	// 몬스터 이미지 크기
	m_ImgWidth = 8;
	m_ImgHeight = 8;

	m_CheckCountX = 1;
	m_CheckCountY = 1;

	// 스프라이트 정보를 초기화합니다.
	m_SpriteTime = 50; // 0.1초
	m_SpriteXIndex = 12;
	m_SpriteYIndex = 18;
	m_SpriteStartIndex = 18;
	m_SpriteEndIndex = 21;
	m_SpriteX = false;
	m_SpriteY = true;

	m_DirTopBottom = 0;
	m_DirLeftRight = 0;

	m_count = 0;
	m_state = 0;
	m_Gravity = 0.0f;
	m_Speed = 9.0f;				// 움직일 때 사용될 속도
	m_MaxSpeed = 6.0f;
	m_canLeft = true;
	m_canRight = false;

	m_ObjectType = 3;
	m_UseCollision = true;
	m_ItemType = 2;

	m_secure = false;
	m_chkColl = false;

	m_dwTime = GetTickCount();
}

void Bullet::Update()
{
	MoveUpdate();

	Scroll();

	UpdateRect();

	BaseUpdate();
}

void Bullet::Render(HDC memDC, HDC backMemDC)
{
	BaseRender(memDC, backMemDC);
}

void Bullet::Scroll()
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

void Bullet::SetPos(int x, int y, int dir)
{
	m_DirLeftRight = dir;
	switch (dir)
	{
	case 0:	// 오른쪽 방향
		m_PosX = x + 22;
		m_PosY = y;
		break;
	case 1:	// 왼쪽 방향
		m_PosX = x - 22;
		m_PosY = y;
		break;
	}
	UpdateRect();
}

void Bullet::UpdateRect()
{
	m_Rect = {
		m_PosX - (m_Width / 2),
		m_PosY - (m_Height / 2),
		m_PosX + (m_Width / 2),
		m_PosY + (m_Height / 2) };
}

void Bullet::MoveUpdate()
{
	if (m_UseCollision) {
		// 왼쪽
		if (m_DirLeftRight == 1 && m_dwTime > 2000) {
			m_PosX -= m_Speed;
		}
		// 오른쪽
		else if (m_DirLeftRight == 0 && m_dwTime > 2000) {
			m_PosX += m_Speed;
		}
		m_dwTime = GetTickCount();

		if (m_Gravity > -40 && !m_chkColl) {
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
}

void Bullet::DieMotion()
{
}

