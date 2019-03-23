#pragma once
#include "Define.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "DoubleBuffer.h"
#include "DrawUI.h"
#include "Shape.h"
#include "Board.h"

extern SceneMgr* g_pSM;
extern DoubleBuffer* g_pDB;

class ShapeMgr;
class Stage4_Tetris : public Scene{
public:
	virtual void Init(SceneMgr* pSceneMgr);
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	void	DrawMap();
	DrawUI	m_DrawUI;

private:
	DWORD		m_KeyTime;
	ShapeMgr*	m_pShapeMgr;

	void		m_ShapeInit();		// 블럭 모양 초기화

public:
	Stage4_Tetris();
	~Stage4_Tetris();
};

