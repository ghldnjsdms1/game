#include "main.h"

void Init()
{
	// 더블버퍼 생성
	srand((unsigned int)time(NULL));

	g_pDB = new DoubleBuffer;
	g_pDB->CreateBuffer(CONSOLE_MAX_WIDTH, CONSOLE_MAX_HEIGHT);

	// 씬 매니저 생성
	g_pSM = new SceneMgr;

	// 씬 매니저에 씬들을 등록
	g_pSM->RegisterScene("Menu", new Menu);
	g_pSM->RegisterScene("Stage", new Stage);
	g_pSM->RegisterScene("Stage2", new Stage2);
	g_pSM->RegisterScene("Stage3_EarthWarm", new Stage3_EarthWarm);
	g_pSM->RegisterScene("Stage4_Tetris", new Stage4_Tetris);

	// 처음에 시작할 씬을 설정
	g_pSM->ReserveChangeScene("Menu");
}

void main()
{
	Init(); // 게임 시작 전 초기화

	while (!g_bGameExit)
	{
		// 더블버퍼 지워주기
		g_pDB->ClearBuffer();

		// 씬 업데이트
		g_pSM->Update();

		// 씬 렌더
		g_pSM->Render();

		// 버퍼 교체
		g_pDB->FlippingBuffer();
	}

	// 메모리 해제
	delete g_pSM, g_pDB;
}