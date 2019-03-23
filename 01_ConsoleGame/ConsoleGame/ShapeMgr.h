#pragma once
#include "Define.h"
//#include "Shape_Rect.h"

class Shape;
//class Shape_Rect;
class ShapeMgr{
public:
	ShapeMgr();
	~ShapeMgr();

public:
	void RegisterShape(const SHAPE_TYPE& eType, Shape* pShape);
	void ReserveChangeShape(const SHAPE_TYPE& eType);
	void ReserveShape(const SHAPE_TYPE& eType);
	void Update();
	void Render();

private:
	Shape*	m_pCurrentShape;
	Shape*	m_pReserveShape;

	map<SHAPE_TYPE, Shape*> m_ShapeContainer;	// 모든 도형을 보관할 공간


};

