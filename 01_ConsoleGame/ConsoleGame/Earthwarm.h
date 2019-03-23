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

extern DoubleBuffer* g_pDB; // 더블버퍼 전역변수 가져오기

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
	CListNode*	m_pBegin;			// 첫번째 노드 주소정보를 갖고있는 노드
	CListNode*	m_pEnd;				// 마지막 노드 주소정보를 갖고있는 노드
	int			m_iSize;			// 노드 개수
	int			m_TotalScore;		// 총 점수
	int			m_Level;			// 난이도레벨
	int			m_Speed;			// 지렁이 스피드
	Food		m_food;				// 음식


	void Init();					// 지렁이 모든 정보 초기화
	void InitNode();				// 노드 1, 2번 초기설정
	void InitList();				// 리스트 초기화
	void ClearNode();				// 노드 모두 제거
	void AutoUpdate_Check();		// 지렁이 자동이동하는데에 체크
	void AutoUpdate();				// 지렁이 자동이동
	void KeyUpdate();				// 키입력을 통해 방향전환
	void EatUpdate();				// 음식 먹었을때 이벤트처리
	void Push_Back();				// 노드 추가
	bool Crash_Check();				// 벽에 부딪치는 여부
	bool Eat_Check();				// 음식 먹었는지 여부
	bool Level_Check();				// 난이도 상승했는지 여부
	void LevelUp();					// 난이도 상승
	void SumScore();				// 점수 합산

public:
	CList() {
		// 노드의 주소정보를 갖고있는 리스트를 처음과 끝에 저장
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