#pragma once
#include "WndDefine.h"

class Button
{
public:
	Button();
	virtual ~Button();

// Variable__
private:
	// ��ư�� �����Դϴ�.(0 : NULL / 1 : OVER / 2 : PRESSED)
	int				m_State		= 0;
	
	// ��ư�� ���� �̹���
	HBITMAP			m_Image;

public:
	// Over �Ӽ��� ����� ������ �����մϴ�.
	bool			m_UseOver	= false;
	
	RECT			m_Rect;

	// ��ư�� ��ġ
	int				m_PosX		= 0;
	int				m_PosY		= 0;

	// ��ư�� ���� ���� ũ��
	int				m_Width		= 0;
	int				m_Height	= 0;

	// ��ư�� ǥ���� �̹��� ũ�⸦ �����մϴ�.(�ڸ�ũ��)
	int				m_ImgWidth	= 0;
	int				m_ImgHeight = 0;

	// ������� ����� ������ �����մϴ�.
	bool			m_UseTransparent	= false;

	// �����ϰ� ó���� ������ �����մϴ�.
	UINT			TransparentColor	= NULL;

	// ��ư�� �����ִ��� üũ�մϴ�.
	bool			m_IsPressed			= false;

	// ��ư�� Ŭ���Ǿ����� üũ�մϴ�.
	bool			m_IsClicked			= false;

// Method__
private:

public:
	void			UpdateRect();
	void			LoadImg(LPCWSTR path, int width, int height);
	
	// ��ư�� ���¸� üũ�մϴ�.(�����ɴϴ�.)
	// (0 : NULL / 1 : OVER / 2 : PRESSED)
	int				CheckBtnState();

	// ��ư�� ���ȴ��� üũ�մϴ�.
	bool			ClickCheck();

	// �ڽ� ��ü�� Update�� Render���� �� ȣ���� �־���մϴ�.
	void			BaseUpdate();
	void			BaseRender(HDC memDC, HDC backMemDC);

	virtual void	Init()								PURE;
	virtual void	Update()							PURE;
	virtual void	Render(HDC memDC, HDC backMemDC)	PURE;

};

