#pragma once

class ShapeMgr;
class Shape {
public:
	virtual void Init() = 0;					// 초기화
	virtual void Update() = 0;					// 이벤트 처리
	virtual void Render() = 0;					// 그리기
	virtual void Release() = 0;					// 메모리 해제

public:
	

protected:
	//ShapeMgr* m_pShapeMgr;

	int		m_ArrShape[4][4];
	int		m_iType;
	int		m_posX;
	int		m_posY;

};