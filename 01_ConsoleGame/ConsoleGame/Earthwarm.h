#pragma once
#include "Object.h"
#include "DoubleBuffer.h"
#include "Food.h"

enum DIR {
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT
};

extern DoubleBuffer* g_pDB; // ������� �������� ��������

class Earthwarm : public Object{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	bool	m_head;
	int		m_posX;
	int		m_posY;
	int		m_dir;

public:
	Earthwarm();
	~Earthwarm();
};

class CListNode {
public:
	Earthwarm		m_EW;
	CListNode*		m_pNext;
	CListNode*		m_pPrev;

public:
	CListNode() :
		m_pNext(NULL), m_pPrev(NULL)
	{}
	~CListNode() {}

};

class CList {

public:
	CListNode*	m_pBegin;			// ù��° ��� �ּ������� �����ִ� ���
	CListNode*	m_pEnd;				// ������ ��� �ּ������� �����ִ� ���
	int			m_iSize;			// ��� ����
	int			m_TotalScore;		// �� ����
	int			m_Level;			// ���̵�����
	int			m_Speed;			// ������ ���ǵ�
	Food		m_food;				// ����


	void Init();					// ������ ��� ���� �ʱ�ȭ
	void InitNode();				// ��� 1, 2�� �ʱ⼳��
	void InitList();				// ����Ʈ �ʱ�ȭ
	void ClearNode();				// ��� ��� ����
	void AutoUpdate_Check();		// ������ �ڵ��̵��ϴµ��� üũ
	void AutoUpdate();				// ������ �ڵ��̵�
	void KeyUpdate();				// Ű�Է��� ���� ������ȯ
	void EatUpdate();				// ���� �Ծ����� �̺�Ʈó��
	void Push_Back();				// ��� �߰�
	bool Crash_Check();				// ���� �ε�ġ�� ����
	bool Eat_Check();				// ���� �Ծ����� ����
	bool Level_Check();				// ���̵� ����ߴ��� ����
	void LevelUp();					// ���̵� ���
	void SumScore();				// ���� �ջ�

public:
	CList() {
		// ����� �ּ������� �����ִ� ����Ʈ�� ó���� ���� ����
		m_pBegin = new CListNode;
		m_pEnd = new CListNode;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_pBegin->m_pPrev = NULL;
		m_pEnd->m_pNext = NULL;

		m_iSize = 0;
		m_TotalScore = 0;
		m_Level = 1;
		m_Speed = WARM_SPEED - (m_Level * 40);
		m_food = {};
	}
	~CList() {
		ClearNode();
		delete m_pBegin;
		delete m_pEnd;
	}
};