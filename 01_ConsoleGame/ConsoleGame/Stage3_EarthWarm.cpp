#include "Stage3_EarthWarm.h"



void Stage3_EarthWarm::Init(SceneMgr * pSceneMgr){
	m_pSceneMgr = pSceneMgr;

	m_KeyTime = GetTickCount();
	m_tList.Init();
}

void Stage3_EarthWarm::Update(){
	// ������ �����Ǿ� �����ʴٸ� �÷��̾� ������Ʈ
	if (!m_DrawUI.m_GamePause){
		// ������ �ð� ������
		if (GetTickCount() - m_KeyTime > m_tList.m_Speed) {
			// ������ �ڵ� �̵�
			m_tList.AutoUpdate_Check();
	
			// ������ �ʱ�ȭ
			m_KeyTime = GetTickCount();
		}
		// Ű �Է����� ��
		m_tList.KeyUpdate();
	}
	else
		m_DrawUI.Update();

	m_DrawUI.m_Pause();
}

void Stage3_EarthWarm::Render(){
	DrawMap();
	DrawFood();
	DrawWarm();

	if (m_DrawUI.m_GamePause) m_DrawUI.Render();
}

void Stage3_EarthWarm::Release(){
}

void Stage3_EarthWarm::DrawMap(){
	// (4,3)~(58, 16)
	SetConsoleTextAttribute(g_pDB->GetBuffer(), CYAN);
	g_pDB->WriteBuffer(2, 1, "�������������������������������");

	for (int i = 2; i < 17; ++i)
	{
		g_pDB->WriteBuffer(2, i, "��");
		g_pDB->WriteBuffer(60, i, "��");
	}

	g_pDB->WriteBuffer(2, 17, "�������������������������������");
	SetConsoleTextAttribute(g_pDB->GetBuffer(), RED);
	g_pDB->WriteBuffer(63, 2, "���̵� : ");
	g_pDB->WriteBuffer(72, 2, CharFromNumber(m_tList.m_Level));
	g_pDB->WriteBuffer(73, 2, "�ܰ�");
	g_pDB->WriteBuffer(63, 4, "������ ũ�� : ");
	g_pDB->WriteBuffer(77, 4, CharFromNumber(m_tList.m_iSize));
	g_pDB->WriteBuffer(78, 4, "��");
	g_pDB->WriteBuffer(63, 6, "���� : ");
	g_pDB->WriteBuffer(72, 6, CharFromNumber(m_tList.m_TotalScore));
	g_pDB->WriteBuffer(76, 6, "��");
	SetConsoleTextAttribute(g_pDB->GetBuffer(), WHITE);
}

void Stage3_EarthWarm::DrawWarm(){
	CListNode*	pNode = m_tList.m_pBegin->m_pNext;

	g_pDB->WriteBuffer(pNode->m_EW.m_posX, pNode->m_EW.m_posY, "��");
	pNode = pNode->m_pNext;

	while (pNode != m_tList.m_pEnd) {
		g_pDB->WriteBuffer(pNode->m_EW.m_posX, pNode->m_EW.m_posY, "��");
		pNode = pNode->m_pNext;
	}
}

void Stage3_EarthWarm::DrawFood(){
	m_tList.m_food.Render();
}

char* Stage3_EarthWarm::CharFromNumber(const int value){
	return _itoa(value, m_Arr, 10);
}

Stage3_EarthWarm::Stage3_EarthWarm()
{
}


Stage3_EarthWarm::~Stage3_EarthWarm()
{
}
