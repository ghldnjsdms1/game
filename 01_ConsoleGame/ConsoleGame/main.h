#pragma once
#include "Define.h"
#include "SceneMgr.h"
#include "Menu.h"
#include "Stage.h"
#include "Stage2.h"
#include "Stage3_EarthWarm.h"
#include "Stage4_Tetris.h"
#include "DoubleBuffer.h"

void Init();				// 게임 시작 되기 전에 초기화

bool g_bGameExit = false;	// 게임 종료
SceneMgr* g_pSM;			// 씬 매니저
DoubleBuffer* g_pDB;		// 더블버퍼


