#include "Stage4_Tetris.h"
#include "Shape_Rect.h"
#include "Shape_Stick.h"
#include "ShapeMgr.h"

void Stage4_Tetris::Init(SceneMgr * pSceneMgr){
	m_pSceneMgr = pSceneMgr;

	m_KeyTime = GetTickCount();
	m_ShapeInit();

}

void Stage4_Tetris::Update(){
	/*if () {
		int tempRand = rand() % SR_END;
		switch (tempRand) {
		case SR_RECT:
			m_pShapeMgr->ReserveChangeShape(SR_RECT);
			break;
		case SR_STICK:
			m_pShapeMgr->ReserveChangeShape(SR_STICK);
			break;
		}
	}*/
	/*if (GetTickCount() - m_KeyTime > 500) {
		m_pShapeMgr->Update();
		m_KeyTime = GetTickCount();
	}*/
	m_pShapeMgr->Update();
	
	
	
}

void Stage4_Tetris::Render(){
	DrawMap();

	m_pShapeMgr->Render();
}

void Stage4_Tetris::Release()
{
}

void Stage4_Tetris::DrawMap(){
	// (2,1)~(, 16)
	SetConsoleTextAttribute(g_pDB->GetBuffer(), CYAN);
	g_pDB->WriteBuffer(2, 1, "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á");
	for (int i = 2; i < 22; ++i)
	{
		g_pDB->WriteBuffer(2, i, "¡á");
		g_pDB->WriteBuffer(24, i, "¡á");
	}
	g_pDB->WriteBuffer(2, 22, "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á");

	g_pDB->WriteBuffer(26, 1, "¡á¡á¡á¡á¡á¡á");
	for (int i = 2; i < 6; ++i) {
		g_pDB->WriteBuffer(36, i, "¡á");
	}
	g_pDB->WriteBuffer(26, 6, "¡á¡á¡á¡á¡á¡á");
	SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
}

void Stage4_Tetris::m_ShapeInit(){
	m_pShapeMgr = new ShapeMgr;

	Shape* tempRect = new Shape_Rect;
	Shape* tempStick = new Shape_Stick;
	m_pShapeMgr->RegisterShape(SR_RECT, tempRect);
	m_pShapeMgr->RegisterShape(SR_STICK, tempStick);

	m_pShapeMgr->ReserveChangeShape(SR_RECT);

}

Stage4_Tetris::Stage4_Tetris()
{
}


Stage4_Tetris::~Stage4_Tetris()
{
}
