#include "Button.h"
#include "GameManager.h"


Button::Button()
{
}


Button::~Button()
{
	if (m_Image != NULL)
		DeleteObject(m_Image);
}

void Button::UpdateRect()
{
	m_Rect = {
		m_PosX - (m_Width / 2),
		m_PosY - (m_Height / 2),
		m_PosX + (m_Width / 2),
		m_PosY + (m_Height / 2)
	};
}

void Button::LoadImg(LPCWSTR path, int width, int height)
{
	m_Image = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
}

int Button::CheckBtnState()
{
	return m_State;
}

bool Button::ClickCheck()
{
	if (m_State == 1 && !m_IsPressed && m_IsClicked) {
		m_IsClicked = false;
		return true;
	}
	return false;
}

void Button::BaseUpdate()
{
	POINT l_MousePos = GameManager::GetGameManager()->GetMouseManager()->GetClientMousePosition();

	// PtINRect() : RECT 와 POINT 간의 충돌여부를 검사합니다.
	if (PtInRect(&m_Rect, l_MousePos)) {
		if (GetAsyncKeyState(VK_LBUTTON)) {
			if (m_State != 2)
				m_State = 2;	// Pressed

			if (!m_IsPressed)
				m_IsPressed = true;

			if (!m_IsClicked)
				m_IsClicked = true;
		}
		else {
			if(m_State != 1)
				m_State = 1;	// Over

			if (m_IsPressed)
				m_IsPressed = false;
		}
	}
	else {
		// 만약 버튼을 누른상태로 버튼 범위를 마우스가 벗어났다면
		// 클릭됨 상태를 false 로 변경합니다.
		if (m_State == 0 && m_IsClicked) {
			m_IsClicked = false;
		}

		if(m_State != 0)
			m_State = 0;	// Normal
	}
}

void Button::BaseRender(HDC memDC, HDC backMemDC)
{
	SelectObject(memDC, m_Image);

	if (m_UseOver) {
		TransparentBlt(
			backMemDC,
			m_Rect.left, m_Rect.top, m_Width, m_Height,
			memDC,
			0, (m_State * m_ImgHeight),
			m_ImgWidth, m_ImgHeight,
			(m_UseTransparent) ? TransparentColor : NULL
		);
	}
	else {
		TransparentBlt(
			backMemDC,
			m_Rect.left, m_Rect.top, m_Width, m_Height,
			memDC,
			0, ((m_UseOver > 1) ? m_ImgHeight : 0),
			m_ImgWidth, m_ImgHeight,
			(m_UseTransparent) ? TransparentColor : NULL
		);
	}
}
