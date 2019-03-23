#include "Object.h"
#include "CharacterManager.h"


Object::Object()
{
}


Object::~Object()
{
	if (m_Image != NULL) DeleteObject(m_Image);
}

void Object::SetActive(bool active)
{
	m_Active = active;
}

bool Object::GetActive()
{
	return m_Active;
}

void Object::SetShowRect(bool show)
{
	m_ShowRect = show;
}

bool Object::GetShowRect()
{
	return m_ShowRect;
}

void Object::SetDrawOnlyTitle(bool draw)
{
	m_OnlyTitle = draw;
}

bool Object::GetDrawOnlyTitle()
{
	return m_OnlyTitle;
}

void Object::SetShowImage(bool show)
{
	m_ShowImage = show;
}

bool Object::GetShowImage()
{
	return m_ShowImage;
}

void Object::UpdateRect()
{
	m_Rect = {
		m_PosX - (m_Width / 2),
		m_PosY - (m_Height / 2),
		m_PosX + (m_Width / 2),
		m_PosY + (m_Height / 2) };
}

void Object::LoadImg(LPCWSTR Path, int width, int height)
{
	m_Image = (HBITMAP)LoadImage(NULL, Path, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
}

bool Object::ImageNullCheck()
{
	if (m_Image == NULL) {
		return true;
	}

	return false;
}

void Object::Scroll()
{
	if (m_useScroll) {
		if (m_PosX < 200) {
			m_Scroll.x = m_passScroll.x;
		}
		else if (m_PosX - 200 >= m_passScroll.x) {
			m_passScroll.x = m_PosX - 200;
			m_Scroll.x = m_passScroll.x;
		}
		else {
			m_Scroll.x = m_passScroll.x;
		}
	}
}

POINT Object::GetScroll()
{
	return m_Scroll;
}

void Object::DieMotion()
{

}

bool Object::DieTimer()
{
	if (GetTickCount() - m_dieTime > 500) {
		return true;
	}
	return false;
}

void Object::MoveUpdate()
{
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

void Object::CollUpdate(int dir)
{
	if (m_MonsterType == 2 && m_CharLevel == 2) {
		if (dir == 1) {
			SetSprite(6, 0, 6, 7, m_SpriteTime);
		}
		else {
			SetSprite(8, 0, 8, 9, m_SpriteTime);
		}
	}
}

void Object::Direct(int dir)
{
	if (CharacterManager::GetPlayer()->m_currentScene == SCENE_PLAY) {
		m_SpriteXIndex = 4;
	}
	else if (CharacterManager::GetPlayer()->m_currentScene == SCENE_SECOND) {
		m_SpriteXIndex = 13;
	}
	switch (m_wallBreakDir)
	{
	case 5:
		m_Speed = 0.0f;
		m_Gravity = 0.0f;
		m_SpriteYIndex = 0;
		break;
	case 1:
		m_Speed = -2.0f;
		m_Gravity = 15.0;
		m_SpriteYIndex = 2;
		break;
	case 2:
		m_Speed = 2.0f;
		m_Gravity = 15.0f;
		m_SpriteYIndex = 1;
		break;
	case 3:
		m_Speed = 2.0f;
		m_Gravity = 10.0f;
		m_SpriteYIndex = 2;
		break;
	case 4:
		m_Speed = -2.0f;
		m_Gravity = 10.0f;
		m_SpriteYIndex = 1;
		break;
	}
}

void Object::EatItem(int level, int itemtype)
{
	CharacterManager::GetPlayer()->m_totalScore += 1000;
	if (itemtype == 1) {
		switch (level)
		{
		case 0:
			m_CharLevel = 1;
			switch (m_DirLeftRight)
			{
			case 0:
				SetSprite(14, 17, 14, 27, 50);
				break;
			case 1:
				SetSprite(0, 17, 0, 13, 50);
				break;
			}
			SetCollInit(m_Width, m_Height * 2, true, m_Speed);
			SetImgSizeInit(m_ImgWidth, m_ImgHeight * 2);
			m_PosY -= m_Height / 4;
			m_tempPauseTime = GetTickCount();
			m_tempPause = true;
			SetCollTime(1000);
			SetCollPauseTime(1000);
			SetTempPauseTime(1000);
			break;
		case 1:
			m_CharLevel = 2;
			switch (m_DirLeftRight)
			{
			case 0:
				SetSprite(m_SpriteXIndex, 3, 2, 5, 50);
				break;
			case 1:
				SetSprite(m_SpriteXIndex, 3, 2, 5, 50);
				break;
			}
			SetSprite(m_SpriteXIndex, 2, 2, 5, 50);
			SetCollInit(m_Width, m_Height, true, m_Speed);
			SetImgSizeInit(m_ImgWidth, m_ImgHeight);
			m_SpriteX = false;
			m_SpriteY = true;
			m_tempPauseTime = GetTickCount();
			m_tempPause = true;
			SetCollTime(1000);
			SetCollPauseTime(1000);
			SetTempPauseTime(1000);
			break;
		case 2:
			SetCollTime(0);
			SetCollPauseTime(0);
			SetTempPauseTime(0);
			break;
		}
		m_UseCollision = true;
		m_collTime = GetTickCount();
		m_collPause = true;
		m_collPauseTime = GetTickCount();
		UpdateRect();
	}
	else if (m_ItemType == 2) {

		SetCollTime(0);
		SetCollPauseTime(0);
		SetTempPauseTime(0);
	}
}

void Object::CollMonster(int level, int monstertype)
{
	switch (level)
	{
	case 0:
		// 게임 재시작
		SetSprite(14, 2, 14, 14, m_SpriteTime);
		m_secure = false;
		m_CharLevel = -1;
		m_Gravity = 15.0f;
		m_state = 1;

		SetCollTime(3000);
		SetCollPauseTime(2000);
		SetTempPauseTime(500);
		break;
	case 1: case 2:
		m_CharLevel = 0;
		switch (m_DirLeftRight)
		{
		case 0:
			SetSprite(14, 18, 14, 27, m_SpriteTime);
			break;
		case 1:
			SetSprite(0, 18, 0, 13, m_SpriteTime);
			break;
		}
		SetCollTime(5000);
		SetCollPauseTime(500);
		SetTempPauseTime(500);
		break;
	}
	//m_UseCollision		= false;
	m_secure2			= true;
	m_tempPause			= true;
	m_collPause			= true;
	m_tempPauseTime		= GetTickCount();
	m_collTime			= GetTickCount();
	m_collPauseTime		= GetTickCount();
	UpdateRect();
}

void Object::LevelUp()
{
}

void Object::SetSprite(int x, int y, int start, int end, int time)
{
	m_SpriteXIndex = x;
	m_SpriteYIndex = y;
	m_SpriteStartIndex = start;
	m_SpriteEndIndex = end;
	m_SpriteTime = time;
}

void Object::SetCollInit(int w, int h, int usecoll, int speed)
{
	m_Width = w;
	m_Height = h;
	m_UseCollision = usecoll;
	m_Speed = speed;
}

void Object::SetImgSizeInit(int iw, int ih)
{
	m_ImgWidth = iw;
	m_ImgHeight = ih;
}

int Object::GetSpriteXIndex()
{
	return m_SpriteXIndex;
}

int Object::GetSpriteYIndex()
{
	return m_SpriteYIndex;
}

int Object::GetSpriteStartIndex()
{
	return m_SpriteStartIndex;
}

int Object::GetSpriteEndIndex()
{
	return m_SpriteEndIndex;
}

void Object::SetDieTime(DWORD time)
{
	m_dieTime = time;
}

void Object::SetCollTime(DWORD time)
{
	m_useCollTime = time;
}

void Object::SetCollPauseTime(DWORD time)
{
	m_useCollPauseTime = time;
}

void Object::SetTempPauseTime(DWORD time)
{
	m_useTempPauseTime = time;
}

void Object::BaseUpdate()
{
	if (m_UseSprite) {
		// 만약 지정한 스프라이트 딜레이가 지난다면
		if (GetTickCount() - m_SpriteAnimTime > m_SpriteTime) {
			m_SpriteAnimTime = GetTickCount();
			if (m_SpriteX) {
				m_SpriteXIndex++;
				m_SpriteXIndex = (m_SpriteXIndex > m_SpriteEndIndex) ? m_SpriteStartIndex : m_SpriteXIndex;
			}
			else if (m_SpriteY) {
				m_SpriteYIndex++;
				m_SpriteYIndex = (m_SpriteYIndex > m_SpriteEndIndex) ? m_SpriteStartIndex : m_SpriteYIndex;
			}
		}
	}
}

void Object::BaseRender(HDC memDC, HDC backMemDC)
{
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
				if (m_SpriteX) {
					TransparentBlt(
						backMemDC,
						m_Rect.left - m_Scroll.x, m_Rect.top, m_Width, m_Height,
						memDC,
						(m_SpriteXIndex * m_ImgWidth), (m_SpriteYIndex * m_ImgHeight), m_ImgWidth, m_ImgHeight,
						// 투명색을 사용중이라면 TransparentColor를, 아니라면 NULL을 넣어서 투명색을 사용하지 않도록 설정
						(m_UseTrasparent) ? TransparentColor : NULL);
				}
				else {
					TransparentBlt(
						backMemDC,
						m_Rect.left - m_Scroll.x, m_Rect.top, m_Width, m_Height,
						memDC,
						(m_SpriteXIndex * m_ImgWidth),
						m_ObjectType == 0 ? m_SpriteYIndex * (m_ImgHeight + 16) : (m_SpriteYIndex * m_ImgHeight),
						m_ImgWidth, m_ImgHeight,
						// 투명색을 사용중이라면 TransparentColor를, 아니라면 NULL을 넣어서 투명색을 사용하지 않도록 설정
						(m_UseTrasparent) ? TransparentColor : NULL);
				}
			}
			// 스프라이트를 사용중이 아니라면
			else {
				TransparentBlt(
					backMemDC,
					m_Rect.left - m_Scroll.x, m_Rect.top, m_Width, m_Height,
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
