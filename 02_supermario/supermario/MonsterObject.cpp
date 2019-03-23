#include "MonsterObject.h"


MonsterObject::MonsterObject()
{
}


MonsterObject::~MonsterObject()
{
	//if (m_Image != NULL) DeleteObject(m_Image);
}

void MonsterObject::SetActive(bool active)
{
	m_Active = active;
}

bool MonsterObject::GetActive()
{
	return m_Active;
}

void MonsterObject::SetShowRect(bool show)
{
	m_ShowRect = show;
}

bool MonsterObject::GetShowRect()
{
	return m_ShowRect;
}

void MonsterObject::SetDrawOnlyTitle(bool draw)
{
	m_OnlyTitle = draw;
}

bool MonsterObject::GetDrawOnlyTitle()
{
	return m_OnlyTitle;
}

void MonsterObject::SetShowImage(bool show)
{
	m_ShowImage = show;
}

bool MonsterObject::GetShowImage()
{
	return m_ShowImage;
}

void MonsterObject::UpdateRect()
{
	m_Rect = {
		m_PosX - (m_Width / 2),
		m_PosY - (m_Height / 2),
		m_PosX + (m_Width / 2),
		m_PosY + (m_Height / 2) };
}

void MonsterObject::LoadImg(LPCWSTR Path, int width, int height)
{
	m_Image = (HBITMAP)LoadImage(NULL, Path, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
}

bool MonsterObject::ImageNullCheck()
{
	if (m_Image == NULL) {
		return true;
	}

	return false;
}

void MonsterObject::Scroll()
{
	if (m_PosX > 200) {
		m_Scroll.x = m_PosX - 200;
	}
	else {
		m_Scroll.x = 0;
	}
}

void MonsterObject::BaseUpdate()
{
	if (m_UseSprite) {
		// 만약 지정한 스프라이트 딜레이가 지난다면
		if (GetTickCount() - m_SpriteAnimTime > m_SpriteTime) {
			m_SpriteAnimTime = GetTickCount();
			m_SpriteXIndex++;

			m_SpriteXIndex = (m_SpriteXIndex > m_SpriteEndIndex) ? m_SpriteStartIndex : m_SpriteXIndex;
		}
	}
}

void MonsterObject::BaseRender(HDC memDC, HDC backMemDC)
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
				TransparentBlt(
					backMemDC,
					m_Rect.left - m_Scroll.x, m_Rect.top, m_Width, m_Height,
					memDC,
					(m_SpriteXIndex * m_ImgWidth), (m_SpriteYIndex * m_ImgHeight), m_ImgWidth, m_ImgHeight,
					// 투명색을 사용중이라면 TransparentColor를, 아니라면 NULL을 넣어서 투명색을 사용하지 않도록 설정
					(m_UseTrasparent) ? TransparentColor : NULL);
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
