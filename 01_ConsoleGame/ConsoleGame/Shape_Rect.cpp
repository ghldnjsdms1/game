#include "Shape_Rect.h"


void Shape_Rect::Init() {
	m_KeyTime = GetTickCount();
	m_AutoTime = GetTickCount();
	m_iType = SR_RECT;

	m_ArrShape[4][4] = { 0, };
	m_ArrShape[1][2] = 1;
	m_ArrShape[2][2] = 1;
	m_ArrShape[1][3] = 1;
	m_ArrShape[2][3] = 1;

	m_posX = 5;
	m_posY = 0;
}

void Shape_Rect::Update(){
	if (GetTickCount() - m_AutoTime > 500) {
		MoveDown();
		m_AutoTime = GetTickCount();
	}
	if (GetTickCount() - m_KeyTime > 50) {
		KeyUpdate();
		m_KeyTime = GetTickCount();
	}
}

void Shape_Rect::Render(){
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (m_ArrShape[i][j] == 1) {
				g_pDB->WriteBuffer((m_posX + i) * 2, m_posY + j, "бс");
			}
		}
	}
}

void Shape_Rect::Release()
{
}

void Shape_Rect::MoveDown(){
	if (m_posY > 17) {
		return;
	}
	++m_posY;
}

void Shape_Rect::MoveLeft(){
	if (m_posX < 2)
		return;
	--m_posX;
}

void Shape_Rect::MoveRight(){
	if (m_posX > 8)
		return;
	++m_posX;
}

void Shape_Rect::KeyUpdate(){
	if (GetAsyncKeyState(VK_LEFT)) {
		MoveLeft();
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		MoveRight();
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		MoveDown();
	}
	if (GetAsyncKeyState(VK_UP)) {
		
	}
}


Shape_Rect::Shape_Rect()
{
}


Shape_Rect::~Shape_Rect()
{
}
