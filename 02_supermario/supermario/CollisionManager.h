#pragma once
//#include "SceneManager.h"
#include "Scene.h"
#include "PlayScene.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	// Variable__
private:
	static Scene* pScene;

public:

	// Method__
private:


public:
	static Scene* getInstance();

};

