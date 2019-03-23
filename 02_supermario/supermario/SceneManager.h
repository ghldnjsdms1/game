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

	// 우리가 추가한 씬
	Scene*									m_FirstScene;

public:


// Method__
private:


public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC memDC, HDC backMemDC);

	virtual void LoadMap();

	// 씬을 추가합니다
	void RegisterScene(std::string key, Scene* scene);

	// 씬을 교체합니다.
	void ChangeScene(std::string key);

	// 씬을 파괴합니다.
	void DestroyScene(std::string key);
};

