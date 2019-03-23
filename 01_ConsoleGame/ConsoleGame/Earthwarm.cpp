#include "Earthwarm.h"



void Earthwarm::Init(){
}

void Earthwarm::Update(){
}

void Earthwarm::Render(){
}

void Earthwarm::Release(){
}

Earthwarm::Earthwarm(){
}


Earthwarm::~Earthwarm()
{
}

void CList::Init(){
	InitNode();

	m_TotalScore = 0;
	m_Level = 1;
	m_Speed = WARM_SPEED - (m_Level * 40);
}

void CList::InitNode(){
	InitList();
	
	CListNode*	pNode = m_pBegin->m_pNext;
	
	pNode->m_EW.m_head = true;
	pNode->m_EW.m_dir = DIR_RIGHT;
	pNode->m_EW.m_posX = 8;
	pNode->m_EW.m_posY = 4;

	pNode = pNode->m_pNext;

	pNode->m_EW.m_head = false;
	pNode->m_EW.m_dir = DIR_RIGHT;
	pNode->m_EW.m_posX = 6;
	pNode->m_EW.m_posY = 4;

	m_iSize = 2;

	m_food.Init();		// Ǫ�� ��ǥ �ʱ�ȭ
}

void CList::InitList() {
	CListNode*	pFirstNode = new CListNode;
	CListNode*	pSecondNode = new CListNode;

	m_pBegin->m_pNext = pFirstNode;
	pFirstNode->m_pPrev = m_pBegin;

	pFirstNode->m_pNext = pSecondNode;
	pSecondNode->m_pPrev = pFirstNode;

	pSecondNode->m_pNext = m_pEnd;
	m_pEnd->m_pPrev = pSecondNode;
}

void CList::ClearNode() {
	CListNode*	pNode = m_pBegin->m_pNext;

	while (pNode != m_pEnd) {
		CListNode*	pNext = pNode->m_pNext;
		delete	pNode;
		pNode = pNext;
	}
	m_pBegin->m_pNext = m_pEnd;
	m_pEnd->m_pPrev = m_pBegin;

	m_iSize = 0;
}

void CList::AutoUpdate_Check(){
	// ��尡 ���̳� ���� �ε�ġ���� Ȯ��
	if (Crash_Check()) {
		ClearNode();
		InitNode();
	}
	// ��尡 ������ �Դ��� Ȯ��
	else if (Eat_Check()) {
		EatUpdate();
		AutoUpdate();
	}
	else
		AutoUpdate();
}

void CList::AutoUpdate(){
	CListNode*	pHeadNode = m_pBegin->m_pNext;
	CListNode*	pNode = pHeadNode;

	// �ڵ����� �̵�
	for (int i = 0; i < m_iSize; ++i) {
		if (pNode->m_EW.m_dir == DIR_UP) {
			pNode->m_EW.m_posY -= 1;
		}
		else if (pNode->m_EW.m_dir == DIR_DOWN) {
			pNode->m_EW.m_posY += 1;
		}
		else if (pNode->m_EW.m_dir == DIR_LEFT) {
			pNode->m_EW.m_posX -= 2;
		}
		else if (pNode->m_EW.m_dir == DIR_RIGHT) {
			pNode->m_EW.m_posX += 2;
		}
		pNode = pNode->m_pNext;
	}
	pNode = pHeadNode;
	// �� ��帶�� ������� ����
	for (int i = 0; i < m_iSize - 1; ++i) {
		if (pNode->m_EW.m_posY < pNode->m_pNext->m_EW.m_posY) {
			pNode->m_pNext->m_EW.m_dir = DIR_UP;
		}
		else if (pNode->m_EW.m_posY > pNode->m_pNext->m_EW.m_posY) {
			pNode->m_pNext->m_EW.m_dir = DIR_DOWN;
		}
		else if (pNode->m_EW.m_posX > pNode->m_pNext->m_EW.m_posX) {
			pNode->m_pNext->m_EW.m_dir = DIR_RIGHT;
		}
		else if (pNode->m_EW.m_posX < pNode->m_pNext->m_EW.m_posX) {
			pNode->m_pNext->m_EW.m_dir = DIR_LEFT;
		}
		pNode = pNode->m_pNext;
	}
}

void CList::KeyUpdate() {
	CListNode*	pHeadNode = m_pBegin->m_pNext;

	// Ű �Է�
	if (GetAsyncKeyState(VK_UP))
	{
		if (pHeadNode->m_EW.m_dir == DIR_LEFT || pHeadNode->m_EW.m_dir == DIR_RIGHT)	pHeadNode->m_EW.m_dir = DIR_UP;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		if (pHeadNode->m_EW.m_dir == DIR_LEFT || pHeadNode->m_EW.m_dir == DIR_RIGHT)	pHeadNode->m_EW.m_dir = DIR_DOWN;

	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (pHeadNode->m_EW.m_dir == DIR_UP || pHeadNode->m_EW.m_dir == DIR_DOWN)		pHeadNode->m_EW.m_dir = DIR_LEFT;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (pHeadNode->m_EW.m_dir == DIR_UP || pHeadNode->m_EW.m_dir == DIR_DOWN)		pHeadNode->m_EW.m_dir = DIR_RIGHT;
	}
}

void CList::EatUpdate() {
	Push_Back();
	SumScore();

	CListNode*	pAddNode = m_pEnd->m_pPrev;
	CListNode*	pPrev = pAddNode->m_pPrev;

	// ���� ����� ���� ���� �������� �߰��� ����� ��ġ���� ��������� �ִ´�.
	if (pPrev->m_EW.m_dir == DIR_UP) {
		pAddNode->m_EW.m_posX = pPrev->m_EW.m_posX;
		pAddNode->m_EW.m_posY = pPrev->m_EW.m_posY + 1;
	}
	else if (pPrev->m_EW.m_dir == DIR_DOWN) {
		pAddNode->m_EW.m_posX = pPrev->m_EW.m_posX;
		pAddNode->m_EW.m_posY = pPrev->m_EW.m_posY - 1;
	}
	else if (pPrev->m_EW.m_dir == DIR_LEFT) {
		pAddNode->m_EW.m_posX = pPrev->m_EW.m_posX + 2;
		pAddNode->m_EW.m_posY = pPrev->m_EW.m_posY;
	}
	else if (pPrev->m_EW.m_dir == DIR_RIGHT) {
		pAddNode->m_EW.m_posX = pPrev->m_EW.m_posX - 2;
		pAddNode->m_EW.m_posY = pPrev->m_EW.m_posY;
	}
	pAddNode->m_EW.m_dir = pPrev->m_EW.m_dir;
	pAddNode->m_EW.m_head = false;
	++m_iSize;

	if (Level_Check())
		LevelUp();
	else
		m_food.Init();
}

void CList::Push_Back(){
	CListNode*	pNode = new CListNode;		// �߰��� ���
	CListNode*	pPrev = m_pEnd->m_pPrev;	// �߰��ϱ� �� ������ ���, �߰��� ����� ���� ���

	pPrev->m_pNext = pNode;
	pNode->m_pPrev = pPrev;

	pNode->m_pNext = m_pEnd;
	m_pEnd->m_pPrev = pNode;
}

bool CList::Crash_Check(){
	CListNode*	pHeadNode = m_pBegin->m_pNext;
	CListNode*	pNode = pHeadNode->m_pNext;

	// �ڽ��� ��尡 ���� �ε�ġ�� ��� Ȯ��
	for (int i = 0; i < m_iSize - 1; ++i) {
		if (pHeadNode->m_EW.m_posX == pNode->m_EW.m_posX && pHeadNode->m_EW.m_posY == pNode->m_EW.m_posY)
			return true;
		pNode = pNode->m_pNext;
	}
	// �ڽ��� ��尡 ���� �ε�ġ�� ��� Ȯ��
	// (4,3)~(58, 16) ������ ��� ����
	if (pHeadNode->m_EW.m_posX < 4 || pHeadNode->m_EW.m_posX > 59 || pHeadNode->m_EW.m_posY < 2 || pHeadNode->m_EW.m_posY > 16)
		return true;

	return false;
}

bool CList::Eat_Check(){
	CListNode*	pHeadNode = m_pBegin->m_pNext;
	// �������� ��尡 Ǫ�带 �Ծ��� ��
	if (pHeadNode->m_EW.m_posX == m_food.m_posX && pHeadNode->m_EW.m_posY == m_food.m_posY)
		return true;

	return false;
}

bool CList::Level_Check(){
	CListNode*	pHeadNode = m_pBegin->m_pNext;
	
	if ((m_Level == 1 && m_iSize == 5) || (m_Level == 2 && m_iSize == 6) || (m_Level == 3 && m_iSize == 7))
		return true;
	return false;
}

void CList::LevelUp(){
	ClearNode();
	InitNode();
	++m_Level;
	m_Speed = WARM_SPEED - (m_Level * 40);
}

void CList::SumScore(){
	m_TotalScore += (m_Level * 10);
}
