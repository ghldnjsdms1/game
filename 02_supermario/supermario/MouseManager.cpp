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

	/*Log("���콺 ��ġx : ", mouse.x);
	Log("���콺 ��ġy : ", mouse.y);*/

	return mouse;
}

POINT MouseManager::GetClientMousePosition()
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(*m_hWnd, &mouse);

	/*Log("���콺 ��ġx : ", mouse.x);
	Log("���콺 ��ġy : ", mouse.y);*/

	return mouse;
}
