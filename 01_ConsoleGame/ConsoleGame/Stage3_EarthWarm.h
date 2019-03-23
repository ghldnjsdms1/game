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
	DWORD		m_KeyTime;							// 키 입력시간 체크
	CList		m_tList;							// 지렁이 링크드리스트
	char		m_Arr[256];							// 문자열을 보관할 변수

public:
	Stage3_EarthWarm();
	~Stage3_EarthWarm();
};

