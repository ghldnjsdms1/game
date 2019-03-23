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
	// �������� ��Ÿ��
	// CS_HREDRAW | CS_VREDRAW : �������� ����(�Ǵ� ����) ũ�Ⱑ ����� ��� �����츦 �ٽ� �׸��ϴ�.
	m_WndCls.style = CS_HREDRAW | CS_VREDRAW;

	// �������� �޽��� ó���Լ��� �����մϴ�.
	m_WndCls.lpfnWndProc = WindowProc::WndProc;

	// ������� ���������� ����� ���� �޸�
	// 0 : ��� ����.
	m_WndCls.cbClsExtra = 0;
	m_WndCls.cbWndExtra = 0;

	m_WndCls.hInstance = m_hInstance;


	// â �������� �����մϴ�.
	// IDI_APPLICATION : �⺻���� ������
	// IDI_ASTERISK : !(����ǥ) ����ǥ���� ������
	m_WndCls.hIcon = LoadIcon(0, IDI_APPLICATION);

	// �ش�â�� Ŀ���� �����մϴ�.
	// IDC_ARROW : �⺻ ȭ��ǥ
	m_WndCls.hCursor = LoadCursor(0, IDC_ARROW);

	// �ش� â�� �������� ĥ�� �귯�ø� �����մϴ�.
	m_WndCls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	// �޴� ��� ����
	m_WndCls.lpszMenuName = NULL;

	// �ش�â�� Ŭ���� �̸�
	m_WndCls.lpszClassName = g_WinClassName;


	// "���� ���� Ư���� â�� ����ϰڴ�" ��� �ǹ̷� �ش� WNDCLASS �� ����մϴ�.
	RegisterClass(&m_WndCls);

	// �������� ������ �� ȭ�鸸 ũ�⸦ �������� �����մϴ�.
	AdjustWindowRect(&m_WndRC, WS_OVERLAPPEDWINDOW, false);

	m_hWnd = CreateWindow(
		g_WinClassName,			// Ŭ���� ��
		g_WinTitleName,			// Ÿ��Ʋ �̸�
		WS_OVERLAPPEDWINDOW,	// ������ ��Ÿ��
		GetMiddlePosX(MAIN_WND_WIDTH), GetMiddlePosY(MAIN_WND_HEIGHT),	// �ʱ� ��ġ(Left, Top)
		MAIN_WND_WIDTH, MAIN_WND_HEIGHT,	// â ũ�� ����(Right, Bottom)
		NULL, NULL,				// �θ� ������ �ڵ�, �޴� �ڵ�
		m_hInstance,
		NULL);

	// ������ �����ֱ�
	ShowWindow(m_hWnd, m_ShowCmd);
	UpdateWindow(m_hWnd);


}

void WindowManager::Init()
{
	CreateWnd();
	
	// DC�� ��� ����� 2������ �ֽ��ϴ�.
	// WndProc ���� WM_PAINT ���� ��¹����
	// GetDC�� ��� ����� �ֽ��ϴ�.
	// GetDC�� ����� ���� ���߿� ������ �ؾ��մϴ�.
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
