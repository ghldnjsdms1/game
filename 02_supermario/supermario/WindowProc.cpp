#include "WindowProc.h"



WindowProc::WindowProc()
{
}


WindowProc::~WindowProc()
{
}

// 윈도우 프로시저
// 발생한 메시지에 따라 어떠한 일처리를 하는곳.
LRESULT WindowProc::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		// 창이 생성될때 해당 메시지를 발생시킵니다.
	case WM_CREATE:
		Log("창이 생성됩니다.");
		return 0;

		// 창 크기를 조절 시, 해당메시지를 발생시킵니다.
	case WM_GETMINMAXINFO:
		Log("창의 가로 크기를 고정시킵니다.", MAIN_WND_WIDTH);
		Log("창의 세로 크기를 고정시킵니다.", MAIN_WND_HEIGHT);
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = MAIN_WND_WIDTH;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = MAIN_WND_HEIGHT;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = MAIN_WND_WIDTH;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = MAIN_WND_HEIGHT;
		break;

		// 창이 꺼지는 것을 요청할 때 해당 메시지를 발생시킵니다.
	case WM_DESTROY:
		// 창이 꺼질 때, 프로세스도 같이 종료시킵니다.
		PostQuitMessage(0);
		return 0;
	}

	// 위에서 처리하지 않은 메시지가 발생한다면 
	// DefWindowProc 로 넘겨주어 우리가 별도로 처리하지 않아도 됩니다.
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
