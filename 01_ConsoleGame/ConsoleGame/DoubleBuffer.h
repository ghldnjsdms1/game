#pragma once
#include "Define.h"

class DoubleBuffer
{
public:
	DoubleBuffer();
	~DoubleBuffer();

public:
	HANDLE GetBuffer(); // 현재 사용중인 버퍼 가져오기

	void CreateBuffer(const int& width, const int& height);	 // 버퍼 생성
	void WriteBuffer(int x, int y, char* string);			 // 버퍼 쓰기
	void FlippingBuffer();									 // 버퍼 교체
	void ClearBuffer();										 // 버퍼 지우기
	void DestroyBuffer();									 // 버퍼 해제

private:
	int m_BufferIndex;	// 현재 사용중인 버퍼 인덱스
	HANDLE m_Buffer[2];	// 버퍼 배열
	
	bool CloseHandle(HANDLE& hFile);	// 버퍼 종료
};

