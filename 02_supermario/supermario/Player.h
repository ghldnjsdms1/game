#pragma once
#include "WndDefine.h"
#include "Object.h"
#include "Bullet.h"

enum class Direction { LEFT, RIGHT, UP, DOWN };
enum class Action { MOVE, IDLE };

class Player : public Object
{
public:
	Player();
	virtual ~Player();

	// Variable__
private:
	int		m_cnt = 0;
	bool	m_flagZ;
	int		m_keyZState;

public:
	Direction	m_Dir = Direction::DOWN;		// 방향값
	Action		m_Ac = Action::IDLE;			// 행동값

	list<Object*>						m_BulletList;
	list<Object*>::iterator				iter;

	int		m_life = 2;
	int		m_coinCount = 0;
	int		m_totalScore = 0;
	DWORD	m_liveTime = 200;
	DWORD	m_liveTimeCount = 0;

	CURRENT_SCENE		m_currentScene;
	POINT				m_prevPos[2];

	bool				m_clearScene = false;

	// Method__
private:


public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC memDC, HDC backMemDC);

	void InputKey();		// 키 입력을 처리할 함수
	void DieMotion();
	bool DontCollision();
	bool CollPauseTime();
	bool TempPause();
	void ClearScene();

	int GetLife();
	void SetPos(int x, int y);
	void SetScene(CURRENT_SCENE scene);

	void SceneInit(CURRENT_SCENE scene, int x, int y, bool scroll, int level, bool state);
	void ScrollInit(int x, int y);

	void SceneChange(int level);

	void SetTime(DWORD d);
	void LiveTime();

	static Player*	GetPlayer();
};

