#include "MouseManager.h"



MouseManager::MouseManager(HWND* hWnd)
{
	m_hWnd = hWnd;
}


MouseManager::~MouseManager()
{
}

POINT MouseManager::GetWindowMousePosition()
{
	POINT mouse;
	GetCursorPos(&mouse);

	/*Log("마우스 위치x : ", mouse.x);
	Log("마우스 위치y : ", mouse.y);*/

	return mouse;
}

POINT MouseManager::GetClientMousePosition()
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(*m_hWnd, &mouse);

	/*Log("마우스 위치x : ", mouse.x);
	Log("마우스 위치y : ", mouse.y);*/

	return mouse;
}
