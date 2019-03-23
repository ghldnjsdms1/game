#pragma once
#include "Scene.h"
#include "Define.h"
#include "DoubleBuffer.h"
#include "SceneMgr.h"
#include "Player.h"
#include "DrawUI.h"

extern SceneMgr* g_pSM;		// main.h�� �ִ� g_pSM �ҷ�����
extern DoubleBuffer* g_pDB; // main.h�� �ִ� g_pDB �ҷ�����

class Stage : public Scene
{
public:
	virtual void Init(SceneMgr* pSceneMgr);
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void DrawMap();		// �� �׸���

private:
	DWORD	m_KeyTime;							// Ű �Է½ð� üũ
	Player	m_Player;
	DrawUI	m_DrawUI;

public:
	Stage();
	~Stage();
};