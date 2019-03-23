#pragma once

class ShapeMgr;
class Shape {
public:
	virtual void Init() = 0;					// �ʱ�ȭ
	virtual void Update() = 0;					// �̺�Ʈ ó��
	virtual void Render() = 0;					// �׸���
	virtual void Release() = 0;					// �޸� ����

public:
	

protected:
	//ShapeMgr* m_pShapeMgr;

	int		m_ArrShape[4][4];
	int		m_iType;
	int		m_posX;
	int		m_posY;

};