#pragma once
#include "Scene.h"
#include "DoubleBuffer.h"
#include "SceneMgr.h"
#include "DrawUI.h"

extern bool g_bGameExit;
extern DoubleBuffer* g_pDB;
extern SceneMgr* g_pSM;

class Stage2 : public Scene
{
public:
	Stage2();
	~Stage2();

public:
	virtual void Init(SceneMgr* pSceneMgr);
	virtual void Update();
	virtual void Render();
	virtual void Release();

	DrawUI	m_DrawUI;

public:
	char* GetTileData(int index);

private:
	DWORD m_PlayerX = 1;
	DWORD m_PlayerY = 1;
};


