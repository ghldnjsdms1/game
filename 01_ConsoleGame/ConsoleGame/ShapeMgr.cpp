#include "ShapeMgr.h"
#include "Shape.h"

ShapeMgr::ShapeMgr()
	: m_pCurrentShape(nullptr), m_pReserveShape(nullptr)
{
}


ShapeMgr::~ShapeMgr(){
	map<SHAPE_TYPE, Shape*>::iterator iter = m_ShapeContainer.begin();
	map<SHAPE_TYPE, Shape*>::iterator iterEnd = m_ShapeContainer.end();

	for (; iter != iterEnd; ++iter){
		iter->second->Release();
		delete iter->second;
	}
}


void ShapeMgr::RegisterShape(const SHAPE_TYPE& eType, Shape* pShape){
	// 예외처리 씬의 주소가 없거나 씬의 키값이 없다면 함수를 끝낸다.
	if (pShape == nullptr)
		return;

	// 씬을 담아둘 컨테이너에 끝부분에 씬의 키값과 주소를 넣는다.
	m_ShapeContainer.insert(m_ShapeContainer.end(), pair<SHAPE_TYPE, Shape*>(eType, pShape));
}

void ShapeMgr::ReserveChangeShape(const SHAPE_TYPE& eType){
	// map 자료구조 안에 있는 find 함수를 통해 키값을 기반으로 원하는
	// 노드를 찾아준다.
	map<SHAPE_TYPE, Shape*>::iterator iter = m_ShapeContainer.find(eType);

	// 찾은 노드가 맵안에 존재한다면 교체할 씬에 담아준다.
	if (iter != m_ShapeContainer.end()) m_pReserveShape = iter->second;
	// 찾은 노드가 맵안에 존재하지 않는다면 nullptr를 담아준다.
	else m_pReserveShape = nullptr;
}

void ShapeMgr::ReserveShape(const SHAPE_TYPE & eType){
	// map 자료구조 안에 있는 find 함수를 통해 키값을 기반으로 원하는
	// 노드를 찾아준다.
	map<SHAPE_TYPE, Shape*>::iterator iter = m_ShapeContainer.find(eType);

	// 찾은 노드가 맵안에 존재한다면 교체할 씬에 담아준다.
	if (iter != m_ShapeContainer.end()) m_pReserveShape = iter->second;
	// 찾은 노드가 맵안에 존재하지 않는다면 nullptr를 담아준다.
	else m_pReserveShape = nullptr;
}

void ShapeMgr::Update(){
		// 교체할 씬이 있다면
	if (m_pReserveShape != nullptr)
	{
		// 교체할 씬을 초기화
		m_pReserveShape->Init();
		// 현재 씬을 교체할 씬으로 변경
		m_pCurrentShape = m_pReserveShape;
		// 교체가 끝났으므로 ReserveScene을 비워준다.
		m_pReserveShape = nullptr;
	}

	// 현재 씬이 비어있지 않다면
	if (m_pCurrentShape != nullptr)
	{
		// 현재 씬을 업데이트 한다.
		m_pCurrentShape->Update();
	}
}

void ShapeMgr::Render()
{
	// 현재 씬이 비어있지 않다면
	if (m_pCurrentShape != nullptr)
	{
		// 현재 씬을 렌더링한다.
		m_pCurrentShape->Render();
	}
}


