#include "WindowProc.h"



WindowProc::WindowProc()
{
}


WindowProc::~WindowProc()
{
}

// ������ ���ν���
// �߻��� �޽����� ���� ��� ��ó���� �ϴ°�.
LRESULT WindowProc::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		// â�� �����ɶ� �ش� �޽����� �߻���ŵ�ϴ�.
	case WM_CREATE:
		Log("â�� �����˴ϴ�.");
		return 0;

		// â ũ�⸦ ���� ��, �ش�޽����� �߻���ŵ�ϴ�.
	case WM_GETMINMAXINFO:
		Log("â�� ���� ũ�⸦ ������ŵ�ϴ�.", MAIN_WND_WIDTH);
		Log("â�� ���� ũ�⸦ ������ŵ�ϴ�.", MAIN_WND_HEIGHT);
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = MAIN_WND_WIDTH;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = MAIN_WND_HEIGHT;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = MAIN_WND_WIDTH;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = MAIN_WND_HEIGHT;
		break;

		// â�� ������ ���� ��û�� �� �ش� �޽����� �߻���ŵ�ϴ�.
	case WM_DESTROY:
		// â�� ���� ��, ���μ����� ���� �����ŵ�ϴ�.
		PostQuitMessage(0);
		return 0;
	}

	// ������ ó������ ���� �޽����� �߻��Ѵٸ� 
	// DefWindowProc �� �Ѱ��־� �츮�� ������ ó������ �ʾƵ� �˴ϴ�.
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
