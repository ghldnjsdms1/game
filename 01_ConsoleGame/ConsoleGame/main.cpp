#include "main.h"

void Init()
{
	// ������� ����
	srand((unsigned int)time(NULL));

	g_pDB = new DoubleBuffer;
	g_pDB->CreateBuffer(CONSOLE_MAX_WIDTH, CONSOLE_MAX_HEIGHT);

	// �� �Ŵ��� ����
	g_pSM = new SceneMgr;

	// �� �Ŵ����� ������ ���
	g_pSM->RegisterScene("Menu", new Menu);
	g_pSM->RegisterScene("Stage", new Stage);
	g_pSM->RegisterScene("Stage2", new Stage2);
	g_pSM->RegisterScene("Stage3_EarthWarm", new Stage3_EarthWarm);
	g_pSM->RegisterScene("Stage4_Tetris", new Stage4_Tetris);

	// ó���� ������ ���� ����
	g_pSM->ReserveChangeScene("Menu");
}

void main()
{
	Init(); // ���� ���� �� �ʱ�ȭ

	while (!g_bGameExit)
	{
		// ������� �����ֱ�
		g_pDB->ClearBuffer();

		// �� ������Ʈ
		g_pSM->Update();

		// �� ����
		g_pSM->Render();

		// ���� ��ü
		g_pDB->FlippingBuffer();
	}

	// �޸� ����
	delete g_pSM, g_pDB;
}