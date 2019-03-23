#include "GameManager.h"

GameManager::GameManager()
{
	m_SceneManager = new SceneManager();
}


GameManager::~GameManager()
{
	delete m_SceneManager;
	delete m_WindowManager;
	delete m_MouseManager;
	delete m_ScrollManager;
}


void GameManager::Update()
{
	// IntersectRect
	// 2, 3 ��° ���ڰ��� ��ġ�� true
	// 1��° ���ڰ� : ��ģ�κ��� ����

	GameManager::GetGameManager()->GetSceneManager()->Update();
}

void GameManager::Render(HDC memDC, HDC backMemDC)
{
	GameManager::GetGameManager()->GetSceneManager()->Render(memDC, backMemDC);
}

void GameManager::Loop(HINSTANCE hInstance, int nShowCmd)
{

	m_WindowManager = new WindowManager(hInstance, nShowCmd);
	m_MouseManager = new MouseManager(m_WindowManager->GetWnd());
	m_ScrollManager = new ScrollManager();

	MSG msg;
	msg.message = WM_NULL;

	DWORD dwTime = GetTickCount();

	while (msg.message != WM_QUIT) {

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			if (dwTime < GetTickCount()) {
				dwTime = GetTickCount();

				m_WindowManager->Update();
				m_WindowManager->Render();

				/*m_MouseManager->GetWindowMousePosition();
				m_MouseManager->GetClientMousePosition();*/
			}
		}
	}
}

SceneManager* GameManager::GetSceneManager()
{
	return m_SceneManager;
}

WindowManager * GameManager::GetWindowManager()
{
	return m_WindowManager;
}

MouseManager * GameManager::GetMouseManager()
{
	return m_MouseManager;
}

ScrollManager * GameManager::GetScrollManager()
{
	return m_ScrollManager;
}

GameManager* GameManager::GetGameManager()
{
	static GameManager	gameManager;
	return				&gameManager;
}