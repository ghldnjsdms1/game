#pragma once
#include "WndDefine.h"
#include "WindowProc.h"

class WindowManager
{
public:
	WindowManager(HINSTANCE hInstance, int showCmd);
	~WindowManager();

// Variable__
private:
	HINSTANCE	m_hInstance;
	int			m_ShowCmd;
	RECT		m_WndRC = { 0, 0, MAIN_WND_WIDTH, MAIN_WND_HEIGHT };

	HWND		m_hWnd;
	WNDCLASS	m_WndCls;

	HDC			m_hdc, m_MemDC, m_BackMemDC;

	// 우리가 그릴 이미지
	HBITMAP		m_OldImg;
	HBITMAP		m_BackBmp;


public:


// Method__
private:
	void CreateWnd();

public:
	void Init();		// 생성자 호출 이후에 호출
	void Update();		// 매 프레임마다 호출
	void Render();		// 매 프레임마다 호출

	HWND*	GetWnd();

};

