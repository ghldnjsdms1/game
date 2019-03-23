#pragma once
#include "WndDefine.h"

class MouseManager
{
public:
	MouseManager(HWND* hWnd);
	~MouseManager();

	// Variable__
private:
	HWND* m_hWnd;

public:


	// Method__
private:


public:
	// 모니터 화면을 기준으로 마우스의 좌표값을 받아옵니다.
	POINT	GetWindowMousePosition();

	// 클라이언트 화면을 기준으로 마우스의 좌표값을 받아옵니다.
	POINT	GetClientMousePosition();
};