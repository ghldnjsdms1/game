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

	// �츮�� �׸� �̹���
	HBITMAP		m_OldImg;
	HBITMAP		m_BackBmp;


public:


// Method__
private:
	void CreateWnd();

public:
	void Init();		// ������ ȣ�� ���Ŀ� ȣ��
	void Update();		// �� �����Ӹ��� ȣ��
	void Render();		// �� �����Ӹ��� ȣ��

	HWND*	GetWnd();

};

