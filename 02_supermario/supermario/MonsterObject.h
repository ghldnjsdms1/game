#pragma once
#include "WndDefine.h"

class MonsterObject
{
public:
	MonsterObject();
	virtual ~MonsterObject();

	// Variable__
private:
	// ���� ������Ʈ Ȱ��ȭ ����
	bool		m_Active = false;

	// �׸� �� �ش翵��(RECT)�� �簢���� �׸� ������ �����մϴ�.
	bool		m_ShowRect = false;

	// �簢���� �׸��ٸ� �׵θ��� ǥ���� ������ �����մϴ�.
	bool		m_OnlyTitle = false;

	// �̹����� �������� �����մϴ�.
	bool		m_ShowImage = false;

public:
	// ������� ����� ������ �����մϴ�.
	bool		m_UseTrasparent = false;

	// ��������Ʈ �̹����� ����� ������ �����մϴ�.
	bool		m_UseSprite = false;

	// ������Ʈ�� ������ �̹���
	HBITMAP		m_Image;

	// ������Ʈ�� ������ ��ġ��
	RECT		m_Rect;

	// ������Ʈ�� ��ǥ
	int			m_PosX = 0;
	int			m_PosY = 0;

	// ������Ʈ�� ������ ����, ����ũ��
	int			m_Width = 0;
	int			m_Height = 0;

	// ��������Ʈ�� ����Ѵٸ�
	// ��������Ʈ �ϳ��� ������ ���� ����
	int			m_ImgWidth = 0;
	int			m_ImgHeight = 0;

	// ����(�����ϰ� ó����) ����
	UINT		TransparentColor = RGB(0, 0, 0);

	POINT		m_Scroll;

protected:
	int			m_SpriteTime = 0; // ���� ��������Ʈ ������ ������
	int			m_SpriteXIndex = 0; // ���� ��������Ʈ �ε���(�׸��� �����ϴ� left ���� ��ǥ)
	int			m_SpriteYIndex = 0; // ���� ��������Ʈ �ε���(�׸��� �����ϴ� top ���� ��ǥ)
	int			m_SpriteStartIndex = 0; // �ִϸ��̼� ���� �ε���
	int			m_SpriteEndIndex = 0; // �ִϸ��̼� ���� �ε���
	DWORD		m_SpriteAnimTime = 0; // �ִϸ��̼� �ð��� üũ

									  // Method
private:


public:
	// �ش� ������Ʈ�� Ȱ��ȭ ���¸� �����մϴ�.
	void		SetActive(bool active);
	// ������Ʈ�� Ȱ��ȭ ���¸� ��ȯ�մϴ�.
	bool		GetActive();


	// ������Ʈ ���� �簢���� �׸� ������ �����մϴ�.
	void		SetShowRect(bool show);
	// ������Ʈ ���� �׸��� �簢���� Ȱ��ȭ ���¸� ��ȯ�մϴ�.
	bool		GetShowRect();
	// �簢���� �׸� �� Ÿ��Ʋ�� �׸� ������ �����մϴ�.
	void		SetDrawOnlyTitle(bool draw);
	// Ÿ��Ʋ�� �׸����ִ��� ���¸� ��ȯ�մϴ�.
	bool		GetDrawOnlyTitle();

	// �ش� ������Ʈ�� �̹����� �׸� ������ �����մϴ�.
	void		SetShowImage(bool show);

	// �ش� ������Ʈ�� �̹����� �׸��� �ִ��� ���¸� �����ɴϴ�.
	bool		GetShowImage();

	// RECT�� ���� ���� ��ǥ�� ����ȭ ��ŵ�ϴ�.
	void		UpdateRect();


	// ���� m_Image �� ����ִ��� üũ�ϴ� �޼ҵ�.
	// NULL true �� ��ȯ�մϴ�.
	bool		ImageNullCheck();

	void Scroll();			// ȭ�� ��ũ��

	virtual void Init()								PURE;
	virtual void Update()							PURE;
	virtual void Render(HDC memDC, HDC backMemDC)	PURE;

	// �̹����� �� ���ϰ� �ҷ��������� ����� �Լ��Դϴ�.
	virtual void		LoadImg(LPCWSTR Path, int width, int height);

	void BaseUpdate();
	void BaseRender(HDC memDC, HDC backMemDC);
};

