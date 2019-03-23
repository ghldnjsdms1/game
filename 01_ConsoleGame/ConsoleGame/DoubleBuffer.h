#pragma once
#include "Define.h"

class DoubleBuffer
{
public:
	DoubleBuffer();
	~DoubleBuffer();

public:
	HANDLE GetBuffer(); // ���� ������� ���� ��������

	void CreateBuffer(const int& width, const int& height);	 // ���� ����
	void WriteBuffer(int x, int y, char* string);			 // ���� ����
	void FlippingBuffer();									 // ���� ��ü
	void ClearBuffer();										 // ���� �����
	void DestroyBuffer();									 // ���� ����

private:
	int m_BufferIndex;	// ���� ������� ���� �ε���
	HANDLE m_Buffer[2];	// ���� �迭
	
	bool CloseHandle(HANDLE& hFile);	// ���� ����
};

