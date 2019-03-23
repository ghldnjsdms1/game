#pragma once
#include "WndDefine.h"

class Button
{
public:
	Button();
	virtual ~Button();

// Variable__
private:
	// 버튼의 상태입니다.(0 : NULL / 1 : OVER / 2 : PRESSED)
	int				m_State		= 0;
	
	// 버튼에 사용될 이미지
	HBITMAP			m_Image;

public:
	// Over 속성을 사용할 것인지 설정합니다.
	bool			m_UseOver	= false;
	
	RECT			m_Rect;

	// 버튼의 위치
	int				m_PosX		= 0;
	int				m_PosY		= 0;

	// 버튼의 가로 세로 크기
	int				m_Width		= 0;
	int				m_Height	= 0;

	// 버튼에 표시할 이미지 크기를 설정합니다.(자를크기)
	int				m_ImgWidth	= 0;
	int				m_ImgHeight = 0;

	// 투명색을 사용할 것인지 지정합니다.
	bool			m_UseTransparent	= false;

	// 투명하게 처리할 색상을 지정합니다.
	UINT			TransparentColor	= NULL;

	// 버튼이 눌려있는지 체크합니다.
	bool			m_IsPressed			= false;

	// 버튼이 클릭되었는지 체크합니다.
	bool			m_IsClicked			= false;

// Method__
private:

public:
	void			UpdateRect();
	void			LoadImg(LPCWSTR path, int width, int height);
	
	// 버튼의 상태를 체크합니다.(가져옵니다.)
	// (0 : NULL / 1 : OVER / 2 : PRESSED)
	int				CheckBtnState();

	// 버튼이 눌렸는지 체크합니다.
	bool			ClickCheck();

	// 자식 객체의 Update와 Render에서 꼭 호출해 주어야합니다.
	void			BaseUpdate();
	void			BaseRender(HDC memDC, HDC backMemDC);

	virtual void	Init()								PURE;
	virtual void	Update()							PURE;
	virtual void	Render(HDC memDC, HDC backMemDC)	PURE;

};

