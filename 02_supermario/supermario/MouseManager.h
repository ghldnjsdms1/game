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
	// ����� ȭ���� �������� ���콺�� ��ǥ���� �޾ƿɴϴ�.
	POINT	GetWindowMousePosition();

	// Ŭ���̾�Ʈ ȭ���� �������� ���콺�� ��ǥ���� �޾ƿɴϴ�.
	POINT	GetClientMousePosition();
};