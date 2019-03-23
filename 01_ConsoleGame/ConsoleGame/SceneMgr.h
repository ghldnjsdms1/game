#pragma once
#include "Define.h"
//////////////////////////////////////
//#include "Scene.h"

// has a ������ �� ���漱���� ���
class Scene;
//////////////////////////////////////
class SceneMgr
{
public:
	void RegisterScene(const string& sceneName, Scene* pScene); // ���ο� ���� ���
	void ReserveChangeScene(const string& sceneName);			// �� ��ȯ	(��ü)
	void Update();												// ���� ������Ʈ
	void Render();												// ���� ����

	Scene* GetReserveScene();

private:
	Scene* m_ReserveScene; // ��ü�� ��
	Scene* m_CurrentScene; // ���� ��

	map<string, Scene*> m_SceneContainer;	// ��� ���� ������ ����

public:
	SceneMgr();
	~SceneMgr();
};

