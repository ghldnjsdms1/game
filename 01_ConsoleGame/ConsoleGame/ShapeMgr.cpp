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
	// ����ó�� ���� �ּҰ� ���ų� ���� Ű���� ���ٸ� �Լ��� ������.
	if (pShape == nullptr)
		return;

	// ���� ��Ƶ� �����̳ʿ� ���κп� ���� Ű���� �ּҸ� �ִ´�.
	m_ShapeContainer.insert(m_ShapeContainer.end(), pair<SHAPE_TYPE, Shape*>(eType, pShape));
}

void ShapeMgr::ReserveChangeShape(const SHAPE_TYPE& eType){
	// map �ڷᱸ�� �ȿ� �ִ� find �Լ��� ���� Ű���� ������� ���ϴ�
	// ��带 ã���ش�.
	map<SHAPE_TYPE, Shape*>::iterator iter = m_ShapeContainer.find(eType);

	// ã�� ��尡 �ʾȿ� �����Ѵٸ� ��ü�� ���� ����ش�.
	if (iter != m_ShapeContainer.end()) m_pReserveShape = iter->second;
	// ã�� ��尡 �ʾȿ� �������� �ʴ´ٸ� nullptr�� ����ش�.
	else m_pReserveShape = nullptr;
}

void ShapeMgr::ReserveShape(const SHAPE_TYPE & eType){
	// map �ڷᱸ�� �ȿ� �ִ� find �Լ��� ���� Ű���� ������� ���ϴ�
	// ��带 ã���ش�.
	map<SHAPE_TYPE, Shape*>::iterator iter = m_ShapeContainer.find(eType);

	// ã�� ��尡 �ʾȿ� �����Ѵٸ� ��ü�� ���� ����ش�.
	if (iter != m_ShapeContainer.end()) m_pReserveShape = iter->second;
	// ã�� ��尡 �ʾȿ� �������� �ʴ´ٸ� nullptr�� ����ش�.
	else m_pReserveShape = nullptr;
}

void ShapeMgr::Update(){
		// ��ü�� ���� �ִٸ�
	if (m_pReserveShape != nullptr)
	{
		// ��ü�� ���� �ʱ�ȭ
		m_pReserveShape->Init();
		// ���� ���� ��ü�� ������ ����
		m_pCurrentShape = m_pReserveShape;
		// ��ü�� �������Ƿ� ReserveScene�� ����ش�.
		m_pReserveShape = nullptr;
	}

	// ���� ���� ������� �ʴٸ�
	if (m_pCurrentShape != nullptr)
	{
		// ���� ���� ������Ʈ �Ѵ�.
		m_pCurrentShape->Update();
	}
}

void ShapeMgr::Render()
{
	// ���� ���� ������� �ʴٸ�
	if (m_pCurrentShape != nullptr)
	{
		// ���� ���� �������Ѵ�.
		m_pCurrentShape->Render();
	}
}


