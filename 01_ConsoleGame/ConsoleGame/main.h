#pragma once
#include "Define.h"
#include "SceneMgr.h"
#include "Menu.h"
#include "Stage.h"
#include "Stage2.h"
#include "Stage3_EarthWarm.h"
#include "Stage4_Tetris.h"
#include "DoubleBuffer.h"

void Init();				// ���� ���� �Ǳ� ���� �ʱ�ȭ

bool g_bGameExit = false;	// ���� ����
SceneMgr* g_pSM;			// �� �Ŵ���
DoubleBuffer* g_pDB;		// �������


