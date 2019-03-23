#pragma once

class SceneMgr;
class Scene
{
public:
	virtual void Init(SceneMgr* pSceneMgr) = 0; // �ʱ�ȭ
	virtual void Update() = 0;					// �̺�Ʈ ó��
	virtual void Render() = 0;					// �׸���
	virtual void Release() = 0;					// �޸� ����

protected:
	SceneMgr* m_pSceneMgr;
};