#pragma once
#include "WndDefine.h"

class MonsterObject
{
public:
	MonsterObject();
	virtual ~MonsterObject();

	// Variable__
private:
	// 현재 오브젝트 활성화 여부
	bool		m_Active = false;

	// 그릴 때 해당영역(RECT)의 사각형도 그릴 것인지 지정합니다.
	bool		m_ShowRect = false;

	// 사각형도 그린다면 테두리만 표시할 것인지 지정합니다.
	bool		m_OnlyTitle = false;

	// 이미지를 띄울것인지 지정합니다.
	bool		m_ShowImage = false;

public:
	// 투명색을 사용할 것인지 지정합니다.
	bool		m_UseTrasparent = false;

	// 스프라이트 이미지를 사용할 것인지 설정합니다.
	bool		m_UseSprite = false;

	// 오브젝트가 가지는 이미지
	HBITMAP		m_Image;

	// 오브젝트가 가지는 위치값
	RECT		m_Rect;

	// 오브젝트의 좌표
	int			m_PosX = 0;
	int			m_PosY = 0;

	// 오브젝트가 가지는 가로, 세로크기
	int			m_Width = 0;
	int			m_Height = 0;

	// 스프라이트를 사용한다면
	// 스프라이트 하나당 가지는 가로 세로
	int			m_ImgWidth = 0;
	int			m_ImgHeight = 0;

	// 숨길(투명하게 처리할) 색상
	UINT		TransparentColor = RGB(0, 0, 0);

	POINT		m_Scroll;

protected:
	int			m_SpriteTime = 0; // 현재 스프라이트 프레임 딜레이
	int			m_SpriteXIndex = 0; // 현재 스프라이트 인덱스(그리기 시작하는 left 시작 좌표)
	int			m_SpriteYIndex = 0; // 현재 스프라이트 인덱스(그리기 시작하는 top 시작 좌표)
	int			m_SpriteStartIndex = 0; // 애니메이션 시작 인덱스
	int			m_SpriteEndIndex = 0; // 애니메이션 종료 인덱스
	DWORD		m_SpriteAnimTime = 0; // 애니메이션 시간을 체크

									  // Method
private:


public:
	// 해당 오브젝트의 활성화 상태를 설정합니다.
	void		SetActive(bool active);
	// 오브젝트의 활성화 상태를 반환합니다.
	bool		GetActive();


	// 오브젝트 위에 사각형을 그릴 것인지 설정합니다.
	void		SetShowRect(bool show);
	// 오브젝트 위에 그리는 사각형의 활성화 상태를 반환합니다.
	bool		GetShowRect();
	// 사각형을 그릴 때 타이틀만 그릴 것인지 설정합니다.
	void		SetDrawOnlyTitle(bool draw);
	// 타이틀만 그리고있는지 상태를 반환합니다.
	bool		GetDrawOnlyTitle();

	// 해당 오브젝트의 이미지를 그릴 것인지 설정합니다.
	void		SetShowImage(bool show);

	// 해당 오브젝트의 이미지를 그리고 있는지 상태를 가져옵니다.
	bool		GetShowImage();

	// RECT의 값을 현재 좌표와 동기화 시킵니다.
	void		UpdateRect();


	// 현재 m_Image 가 비어있는지 체크하는 메소드.
	// NULL true 를 반환합니다.
	bool		ImageNullCheck();

	void Scroll();			// 화면 스크롤

	virtual void Init()								PURE;
	virtual void Update()							PURE;
	virtual void Render(HDC memDC, HDC backMemDC)	PURE;

	// 이미지를 더 편하게 불러오기위해 사용할 함수입니다.
	virtual void		LoadImg(LPCWSTR Path, int width, int height);

	void BaseUpdate();
	void BaseRender(HDC memDC, HDC backMemDC);
};

