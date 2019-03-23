#include "SceneMgr.h"
#include "Scene.h"

SceneMgr::SceneMgr()
	: m_CurrentScene(nullptr), m_ReserveScene(nullptr)
{
}

SceneMgr::~SceneMgr()
{
	for (map<string, Scene*>::iterator iter = m_SceneContainer.begin(); iter != m_SceneContainer.end(); ++iter)
	{
		iter->second->Release();
		delete iter->second;
	}
}

void SceneMgr::RegisterScene(const string & sceneName, Scene * pScene)
{
	// 예외처리 씬의 주소가 없거나 씬의 키값이 없다면 함수를 끝낸다.
	if (pScene == nullptr || sceneName.compare("") == 0)
		return;

	// 씬을 담아둘 컨테이너에 끝부분에 씬의 키값과 주소를 넣는다.
	m_SceneContainer.insert(m_SceneContainer.end(), pair<string, Scene*>(sceneName, pScene));
}

void SceneMgr::ReserveChangeScene(const string & sceneName)
{
	// map 자료구조 안에 있는 find 함수를 통해 키값을 기반으로 원하는
	// 노드를 찾아준다.
	map<string, Scene*>::iterator iter = m_SceneContainer.find(sceneName);
	
	// 찾은 노드가 맵안에 존재한다면 교체할 씬에 담아준다.
	if (iter != m_SceneContainer.end()) m_ReserveScene = iter->second;
	// 찾은 노드가 맵안에 존재하지 않는다면 nullptr를 담아준다.
	else m_ReserveScene = nullptr;
}

void SceneMgr::Update()
{
	// 교체할 씬이 있다면
	if (m_ReserveScene != nullptr)
	{
		// 교체할 씬을 초기화
		m_ReserveScene->Init(this);
		// 현재 씬을 교체할 씬으로 변경
		m_CurrentScene = m_ReserveScene;
		// 교체가 끝났으므로 ReserveScene을 비워준다.
		m_ReserveScene = nullptr;
	}

	// 현재 씬이 비어있지 않다면
	if (m_CurrentScene != nullptr)
	{
		// 현재 씬을 업데이트 한다.
		m_CurrentScene->Update();
	}
}

void SceneMgr::Render()
{
	// 현재 씬이 비어있지 않다면
	if (m_CurrentScene != nullptr)
	{
		// 현재 씬을 렌더링한다.
		m_CurrentScene->Render();
	}
}

Scene * SceneMgr::GetReserveScene()
{
	return m_ReserveScene;
}

