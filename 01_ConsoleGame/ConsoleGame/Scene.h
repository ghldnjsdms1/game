#pragma once

class SceneMgr;
class Scene
{
public:
	virtual void Init(SceneMgr* pSceneMgr) = 0; // 초기화
	virtual void Update() = 0;					// 이벤트 처리
	virtual void Render() = 0;					// 그리기
	virtual void Release() = 0;					// 메모리 해제

protected:
	SceneMgr* m_pSceneMgr;
};