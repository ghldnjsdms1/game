#pragma once
#include "WndDefine.h"
#include <map>
#include <string>
#include "FirstScene.h"
#include "MakeScene.h"
#include "PlayScene.h"
#include "PlayBonusScene.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"
#include "SecondScene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();


// Variable__
private:
	std::map<std::string, Scene*>			SceneList;
	std::map<std::string, Scene*>::iterator iter;

	Scene*									m_PlayScene;
	Scene*									m_DestroyScene;

	// �츮�� �߰��� ��
	Scene*									m_FirstScene;

public:


// Method__
private:


public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC memDC, HDC backMemDC);

	virtual void LoadMap();

	// ���� �߰��մϴ�
	void RegisterScene(std::string key, Scene* scene);

	// ���� ��ü�մϴ�.
	void ChangeScene(std::string key);

	// ���� �ı��մϴ�.
	void DestroyScene(std::string key);
};

