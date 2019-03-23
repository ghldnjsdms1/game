#pragma once
#include "Scene.h"
#include "Define.h"
#include "DoubleBuffer.h"
#include "SceneMgr.h"
#include "Player.h"
#include "DrawUI.h"

extern SceneMgr* g_pSM;		// main.h에 있는 g_pSM 불러오기
extern DoubleBuffer* g_pDB; // main.h에 있는 g_pDB 불러오기

class Stage : public Scene
{
public:
	virtual void Init(SceneMgr* pSceneMgr);
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void DrawMap();		// 맵 그리기

private:
	DWORD	m_KeyTime;							// 키 입력시간 체크
	Player	m_Player;
	DrawUI	m_DrawUI;

public:
	Stage();
	~Stage();
};