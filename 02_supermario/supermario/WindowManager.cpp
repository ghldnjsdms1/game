#include "WindowManager.h"
#include "GameManager.h"


WindowManager::WindowManager(HINSTANCE hInstance, int showCmd)
{
	m_hInstance = hInstance;
	m_ShowCmd = showCmd;

	Init();
}


WindowManager::~WindowManager()
{
	DeleteObject(SelectObject(m_BackMemDC, m_OldImg));
}

void WindowManager::CreateWnd()
{
	// 윈도우의 스타일
	// CS_HREDRAW | CS_VREDRAW : 윈도우의 수직(또는 수평) 크기가 변경될 경우 윈도우를 다시 그립니다.
	m_WndCls.style = CS_HREDRAW | CS_VREDRAW;

	// 윈도우의 메시지 처리함수를 지정합니다.
	m_WndCls.lpfnWndProc = WindowProc::WndProc;

	// 윈도우즈가 내부적으로 사용할 여분 메모리
	// 0 : 사용 안함.
	m_WndCls.cbClsExtra = 0;
	m_WndCls.cbWndExtra = 0;

	m_WndCls.hInstance = m_hInstance;


	// 창 아이콘을 변경합니다.
	// IDI_APPLICATION : 기본적인 아이콘
	// IDI_ASTERISK : !(느낌표) 세모표지판 아이콘
	m_WndCls.hIcon = LoadIcon(0, IDI_APPLICATION);

	// 해당창의 커서를 지정합니다.
	// IDC_ARROW : 기본 화살표
	m_WndCls.hCursor = LoadCursor(0, IDC_ARROW);

	// 해당 창의 배경색상을 칠할 브러시를 지정합니다.
	m_WndCls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	// 메뉴 사용 안함
	m_WndCls.lpszMenuName = NULL;

	// 해당창의 클래스 이름
	m_WndCls.lpszClassName = g_WinClassName;


	// "위와 같은 특성의 창을 사용하겠다" 라는 의미로 해당 WNDCLASS 를 등록합니다.
	RegisterClass(&m_WndCls);

	// 프레임을 제외한 뷰 화면만 크기를 가지도록 설정합니다.
	AdjustWindowRect(&m_WndRC, WS_OVERLAPPEDWINDOW, false);

	m_hWnd = CreateWindow(
		g_WinClassName,			// 클래스 명
		g_WinTitleName,			// 타이틀 이름
		WS_OVERLAPPEDWINDOW,	// 윈도우 스타일
		GetMiddlePosX(MAIN_WND_WIDTH), GetMiddlePosY(MAIN_WND_HEIGHT),	// 초기 위치(Left, Top)
		MAIN_WND_WIDTH, MAIN_WND_HEIGHT,	// 창 크기 설정(Right, Bottom)
		NULL, NULL,				// 부모 윈도우 핸들, 메뉴 핸들
		m_hInstance,
		NULL);

	// 윈도우 보여주기
	ShowWindow(m_hWnd, m_ShowCmd);
	UpdateWindow(m_hWnd);


}

void WindowManager::Init()
{
	CreateWnd();
	
	// DC를 얻는 방법은 2가지가 있습니다.
	// WndProc 에서 WM_PAINT 에서 얻는방법과
	// GetDC로 얻는 방법이 있습니다.
	// GetDC를 사용할 때는 나중에 해제를 해야합니다.
	m_hdc = GetDC(m_hWnd);
	m_BackBmp = NULL;
}

void WindowManager::Update()
{
	GameManager::GetGameManager()->Update();
}

void WindowManager::Render()
{
	m_BackMemDC = CreateCompatibleDC(m_hdc);
	m_MemDC = CreateCompatibleDC(m_hdc);

	m_BackBmp = CreateCompatibleBitmap(m_hdc,
		MAIN_WND_WIDTH, MAIN_WND_HEIGHT);
	m_OldImg = (HBITMAP)SelectObject(m_BackMemDC, m_BackBmp);
	
	//FillRect(m_BackMemDC, &m_WndRC, (HBRUSH)GetStockObject(WHITE_BRUSH));
	FillRect(m_BackMemDC, &m_WndRC, CreateSolidBrush(RGB(104, 128, 248)));
	BitBlt(m_BackMemDC, 0, 0, MAIN_WND_WIDTH, MAIN_WND_HEIGHT, m_MemDC,
		0, 0, SRCCOPY);

	GameManager::GetGameManager()->Render(m_MemDC, m_BackMemDC);

	BitBlt(m_hdc, 0, 0, MAIN_WND_WIDTH, MAIN_WND_HEIGHT, m_BackMemDC,
		0, 0, SRCCOPY);

	DeleteDC(m_BackMemDC);
	DeleteDC(m_MemDC);
	DeleteObject(m_BackBmp);
}

HWND * WindowManager::GetWnd()
{
	return &m_hWnd;
}
