#pragma once
#pragma warning(disable : 4996)
#include "Define.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "DoubleBuffer.h"
#include "Earthwarm.h"
#include "DrawUI.h"


extern SceneMgr* g_pSM;
extern DoubleBuffer* g_pDB;

class Stage3_EarthWarm : public Scene{
public:
	virtual void Init(SceneMgr* pSceneMgr);
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	void	DrawMap();
	void	DrawWarm();
	void	DrawFood();
	DrawUI	m_DrawUI;
	char*	CharFromNumber(const int value);

private:
	DWORD		m_KeyTime;							// Ű �Է½ð� üũ
	CList		m_tList;							// ������ ��ũ�帮��Ʈ
	char		m_Arr[256];							// ���ڿ��� ������ ����

public:
	Stage3_EarthWarm();
	~Stage3_EarthWarm();
};

