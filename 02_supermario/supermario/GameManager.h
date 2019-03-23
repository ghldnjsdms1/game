#pragma once
#include "WndDefine.h"
#include "SceneManager.h"
#include "WindowManager.h"
#include "MouseManager.h"
#include "ScrollManager.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	// Variable__
private:
	SceneManager*	m_SceneManager;
	WindowManager*	m_WindowManager;
	MouseManager*	m_MouseManager;
	ScrollManager*	m_ScrollManager;

public:



	// Method__
private:

public:
	void				Update();
	void				Render(HDC memDC, HDC backMemDC);
	void				Loop(HINSTANCE hInstance, int nShowCmd);

	SceneManager*		GetSceneManager();
	WindowManager*		GetWindowManager();
	MouseManager*		GetMouseManager();
	ScrollManager*		GetScrollManager();

	static GameManager*	GetGameManager();

};