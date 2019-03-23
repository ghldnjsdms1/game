#pragma once
#include "Define.h"
//////////////////////////////////////
//#include "Scene.h"

// has a 관계일 때 전방선언을 사용
class Scene;
//////////////////////////////////////
class SceneMgr
{
public:
	void RegisterScene(const string& sceneName, Scene* pScene); // 새로운 씬을 등록
	void ReserveChangeScene(const string& sceneName);			// 씬 전환	(교체)
	void Update();												// 씬의 업데이트
	void Render();												// 씬의 렌더

	Scene* GetReserveScene();

private:
	Scene* m_ReserveScene; // 교체할 씬
	Scene* m_CurrentScene; // 현재 씬

	map<string, Scene*> m_SceneContainer;	// 모든 씬을 보관할 공간

public:
	SceneMgr();
	~SceneMgr();
};

