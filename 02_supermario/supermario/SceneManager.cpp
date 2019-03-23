#include "SceneManager.h"


SceneManager::SceneManager()
{
	this->Init();
}


SceneManager::~SceneManager()
{
	for (auto it = SceneList.begin(); it != SceneList.end(); it++) {
		delete it->second;
	}
}

void SceneManager::Init()
{
	// 사용할 씬을 이곳에 추가합니다.
	RegisterScene("FirstScene", new FirstScene);
	RegisterScene("MakeScene", new MakeScene);
	RegisterScene("PlayScene", new PlayScene);
	RegisterScene("PlayBonusScene", new PlayBonusScene);
	RegisterScene("MainMenuScene", new MainMenuScene);
	RegisterScene("GameOverScene", new GameOverScene);
	RegisterScene("SecondScene", new SecondScene);

	// 처음 사용될 씬을 설정합니다.
	ChangeScene("MainMenuScene");
	m_PlayScene->Init();
}

void SceneManager::Update()
{
	if (m_PlayScene == nullptr) return;
	m_PlayScene->Update();
}

void SceneManager::Render(HDC memDC, HDC backMemDC)
{
	if (m_PlayScene == nullptr) return;
	m_PlayScene->Render(memDC, backMemDC);
}

void SceneManager::LoadMap()
{
	if (m_PlayScene == nullptr) return;
	m_PlayScene->LoadMap();
}

void SceneManager::RegisterScene(std::string key, Scene * scene)
{
	// key의 값이 공백이거나, Scene이 가리키는 값이 null이라면
	if (key.compare("") == 0 || scene == nullptr) return;

	// 씬을 추가합니다.
	SceneList.insert(make_pair(key, scene));
}

void SceneManager::ChangeScene(std::string key)
{
	bool l_FindScene = false;

	// key와 같은 키값이 현재 SceneList에 존재하는지 검사
	for (auto it = SceneList.begin(); it != SceneList.end(); it++) {
		if (it->first.compare(key) == 0) {
			l_FindScene = true;
			break;
		}
	}
	
	// 만약 찾지 못했다면 씬을 교체하지 않습니다.
	if (!l_FindScene) return;

	// 찾았다면 iterator 가 가리키는 곳을 해당 키의 값으로 설정합니다.
	iter = SceneList.find(key);

	// 현재 실해중인 씬에 해당 Scene을 넣습니다.
	m_PlayScene = iter->second;

	m_PlayScene->Init();
}

void SceneManager::DestroyScene(std::string key)
{
	bool l_FindScene = false;

	// key와 같은 키값이 현재 SceneList에 존재하는지 검사
	for (auto it = SceneList.begin(); it != SceneList.end(); it++) {
		if (it->first.compare(key) == 0) {
			l_FindScene = true;
			break;
		}
	}

	// 만약 찾지 못했다면 씬을 교체하지 않습니다.
	if (!l_FindScene) return;

	// 찾았다면 iterator 가 가리키는 곳을 해당 키의 값으로 설정합니다.
	iter = SceneList.find(key);

	// 현재 실해중인 씬에 해당 Scene을 넣습니다.
	m_DestroyScene = iter->second;

	m_DestroyScene->Destroy();
}
