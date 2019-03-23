#include "DoubleBuffer.h"

DoubleBuffer::DoubleBuffer()
{
	m_BufferIndex = 0;
}

DoubleBuffer::~DoubleBuffer()
{
}

HANDLE DoubleBuffer::GetBuffer()
{
	return m_Buffer[m_BufferIndex];
}

void DoubleBuffer::CreateBuffer(const int & width, const int & height)
{
	CONSOLE_CURSOR_INFO cci;		// 콘솔창 깜빡이는 커서
	COORD size = { width, height }; // 버퍼 크기를 저장하는 구조체
	SMALL_RECT rect;				// 창 크기를 저장하는 구조체

	rect.Left = 0;
	rect.Top = 0;
	rect.Right = width - 1;
	rect.Bottom = height - 1;

	// 1번 버퍼 생성
	m_Buffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(m_Buffer[0], size);	// 버퍼 크기 설정
	SetConsoleWindowInfo(m_Buffer[0], TRUE, &rect); // 창 크기 설정

	// 2번 버퍼 생성
	m_Buffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(m_Buffer[1], size);	// 버퍼 크기 설정
	SetConsoleWindowInfo(m_Buffer[1], TRUE, &rect); // 창 크기 설정

	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(m_Buffer[0], &cci); // 1번 버퍼에 깜빡이는 커서 표시안함
	SetConsoleCursorInfo(m_Buffer[1], &cci); // 2번 버퍼에 깜빡이는 커서 표시안함
}

void DoubleBuffer::WriteBuffer(int x, int y, char * string)
{
	DWORD dw;						 // 좌표 저장 구조체
	COORD CursorPosition = { x, y }; // 좌표 설정

	SetConsoleCursorPosition(m_Buffer[m_BufferIndex], CursorPosition);
	WriteFile(m_Buffer[m_BufferIndex], string, strlen(string), &dw, NULL);
}

void DoubleBuffer::FlippingBuffer()
{
	// 버퍼 전환 속도 설정
	Sleep(30);

	SetConsoleActiveScreenBuffer(m_Buffer[m_BufferIndex]);
	m_BufferIndex = !m_BufferIndex; // 다음 버퍼 선택
}

void DoubleBuffer::ClearBuffer()
{
	COORD coor = { 0,0 };
	DWORD dw;

	// 해당 버퍼의 coor 좌표부터 ' ' 값을 채워서 버퍼를 빈공간으로 바꿈
	FillConsoleOutputCharacter(m_Buffer[m_BufferIndex], ' ',
		CONSOLE_MAX_WIDTH * CONSOLE_MAX_HEIGHT, coor, &dw);
}

void DoubleBuffer::DestroyBuffer()
{
	CloseHandle(m_Buffer[0]);
	CloseHandle(m_Buffer[1]);
}

bool DoubleBuffer::CloseHandle(HANDLE & hFile)
{
	if (INVALID_HANDLE_VALUE != hFile)
	{
		__try {
			return (0 != ::CloseHandle(hFile));
		}
		__finally {
			hFile = INVALID_HANDLE_VALUE;
		}
	}

	return false;
}
