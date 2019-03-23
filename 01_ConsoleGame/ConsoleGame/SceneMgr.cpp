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
	// ����ó�� ���� �ּҰ� ���ų� ���� Ű���� ���ٸ� �Լ��� ������.
	if (pScene == nullptr || sceneName.compare("") == 0)
		return;

	// ���� ��Ƶ� �����̳ʿ� ���κп� ���� Ű���� �ּҸ� �ִ´�.
	m_SceneContainer.insert(m_SceneContainer.end(), pair<string, Scene*>(sceneName, pScene));
}

void SceneMgr::ReserveChangeScene(const string & sceneName)
{
	// map �ڷᱸ�� �ȿ� �ִ� find �Լ��� ���� Ű���� ������� ���ϴ�
	// ��带 ã���ش�.
	map<string, Scene*>::iterator iter = m_SceneContainer.find(sceneName);
	
	// ã�� ��尡 �ʾȿ� �����Ѵٸ� ��ü�� ���� ����ش�.
	if (iter != m_SceneContainer.end()) m_ReserveScene = iter->second;
	// ã�� ��尡 �ʾȿ� �������� �ʴ´ٸ� nullptr�� ����ش�.
	else m_ReserveScene = nullptr;
}

void SceneMgr::Update()
{
	// ��ü�� ���� �ִٸ�
	if (m_ReserveScene != nullptr)
	{
		// ��ü�� ���� �ʱ�ȭ
		m_ReserveScene->Init(this);
		// ���� ���� ��ü�� ������ ����
		m_CurrentScene = m_ReserveScene;
		// ��ü�� �������Ƿ� ReserveScene�� ����ش�.
		m_ReserveScene = nullptr;
	}

	// ���� ���� ������� �ʴٸ�
	if (m_CurrentScene != nullptr)
	{
		// ���� ���� ������Ʈ �Ѵ�.
		m_CurrentScene->Update();
	}
}

void SceneMgr::Render()
{
	// ���� ���� ������� �ʴٸ�
	if (m_CurrentScene != nullptr)
	{
		// ���� ���� �������Ѵ�.
		m_CurrentScene->Render();
	}
}

Scene * SceneMgr::GetReserveScene()
{
	return m_ReserveScene;
}

