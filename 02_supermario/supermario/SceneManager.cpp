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
	// ����� ���� �̰��� �߰��մϴ�.
	RegisterScene("FirstScene", new FirstScene);
	RegisterScene("MakeScene", new MakeScene);
	RegisterScene("PlayScene", new PlayScene);
	RegisterScene("PlayBonusScene", new PlayBonusScene);
	RegisterScene("MainMenuScene", new MainMenuScene);
	RegisterScene("GameOverScene", new GameOverScene);
	RegisterScene("SecondScene", new SecondScene);

	// ó�� ���� ���� �����մϴ�.
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
	// key�� ���� �����̰ų�, Scene�� ����Ű�� ���� null�̶��
	if (key.compare("") == 0 || scene == nullptr) return;

	// ���� �߰��մϴ�.
	SceneList.insert(make_pair(key, scene));
}

void SceneManager::ChangeScene(std::string key)
{
	bool l_FindScene = false;

	// key�� ���� Ű���� ���� SceneList�� �����ϴ��� �˻�
	for (auto it = SceneList.begin(); it != SceneList.end(); it++) {
		if (it->first.compare(key) == 0) {
			l_FindScene = true;
			break;
		}
	}
	
	// ���� ã�� ���ߴٸ� ���� ��ü���� �ʽ��ϴ�.
	if (!l_FindScene) return;

	// ã�Ҵٸ� iterator �� ����Ű�� ���� �ش� Ű�� ������ �����մϴ�.
	iter = SceneList.find(key);

	// ���� �������� ���� �ش� Scene�� �ֽ��ϴ�.
	m_PlayScene = iter->second;

	m_PlayScene->Init();
}

void SceneManager::DestroyScene(std::string key)
{
	bool l_FindScene = false;

	// key�� ���� Ű���� ���� SceneList�� �����ϴ��� �˻�
	for (auto it = SceneList.begin(); it != SceneList.end(); it++) {
		if (it->first.compare(key) == 0) {
			l_FindScene = true;
			break;
		}
	}

	// ���� ã�� ���ߴٸ� ���� ��ü���� �ʽ��ϴ�.
	if (!l_FindScene) return;

	// ã�Ҵٸ� iterator �� ����Ű�� ���� �ش� Ű�� ������ �����մϴ�.
	iter = SceneList.find(key);

	// ���� �������� ���� �ش� Scene�� �ֽ��ϴ�.
	m_DestroyScene = iter->second;

	m_DestroyScene->Destroy();
}
