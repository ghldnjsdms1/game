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
	CONSOLE_CURSOR_INFO cci;		// �ܼ�â �����̴� Ŀ��
	COORD size = { width, height }; // ���� ũ�⸦ �����ϴ� ����ü
	SMALL_RECT rect;				// â ũ�⸦ �����ϴ� ����ü

	rect.Left = 0;
	rect.Top = 0;
	rect.Right = width - 1;
	rect.Bottom = height - 1;

	// 1�� ���� ����
	m_Buffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(m_Buffer[0], size);	// ���� ũ�� ����
	SetConsoleWindowInfo(m_Buffer[0], TRUE, &rect); // â ũ�� ����

	// 2�� ���� ����
	m_Buffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(m_Buffer[1], size);	// ���� ũ�� ����
	SetConsoleWindowInfo(m_Buffer[1], TRUE, &rect); // â ũ�� ����

	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(m_Buffer[0], &cci); // 1�� ���ۿ� �����̴� Ŀ�� ǥ�þ���
	SetConsoleCursorInfo(m_Buffer[1], &cci); // 2�� ���ۿ� �����̴� Ŀ�� ǥ�þ���
}

void DoubleBuffer::WriteBuffer(int x, int y, char * string)
{
	DWORD dw;						 // ��ǥ ���� ����ü
	COORD CursorPosition = { x, y }; // ��ǥ ����

	SetConsoleCursorPosition(m_Buffer[m_BufferIndex], CursorPosition);
	WriteFile(m_Buffer[m_BufferIndex], string, strlen(string), &dw, NULL);
}

void DoubleBuffer::FlippingBuffer()
{
	// ���� ��ȯ �ӵ� ����
	Sleep(30);

	SetConsoleActiveScreenBuffer(m_Buffer[m_BufferIndex]);
	m_BufferIndex = !m_BufferIndex; // ���� ���� ����
}

void DoubleBuffer::ClearBuffer()
{
	COORD coor = { 0,0 };
	DWORD dw;

	// �ش� ������ coor ��ǥ���� ' ' ���� ä���� ���۸� ��������� �ٲ�
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
