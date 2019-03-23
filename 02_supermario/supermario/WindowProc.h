#pragma once
#include "WndDefine.h"

class WindowProc
{
public:
	WindowProc();
	~WindowProc();

public:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

