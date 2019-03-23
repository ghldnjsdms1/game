#pragma once
#include "WndDefine.h"

class Object
{
public:
	Object();
	virtual ~Object();

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
	POINT		m_passScroll;

	int			m_DirTopBottom = 0;
	int			m_DirLeftRight = 0;

	int			m_count = 0;
	int 		m_state = 0;
	float		m_Gravity = 0.0f;
	float		m_MaxGravity = 0.0f;
	float		m_NormalGravity = 0.0f;
	float		m_AccelMaxGravity = 0.0f;
	float		m_AccelGravity = 0.0f;
	float		m_Speed = 0.0f;				// ������ �� ���� �ӵ�
	float		m_MaxSpeed = 0.0f;
	float		m_MinSpeed = 0.0f;
	float		m_NormalSpeed = 0.0f;
	float		m_AccelSpeed = 0.0f;
	bool		m_canLeft = true;
	bool		m_canRight = true;
	bool		m_canBottom = true;

	bool		m_flag = false;
	bool		m_preFlag = false;
	bool		m_keyJumpFlag = false;

	bool		m_chkColl = false;			// �浹 ����
	bool		m_collPause = false;
	bool		m_tempPause = false;

	bool		m_useScroll;

	COLLISION_DIRECTION m_colDirTB = COL_BOTTOM;		// ���� �浹 ���� (top, bottom)
	COLLISION_DIRECTION m_colDirLR = COL_NONE;			// ���� �浹 ���� (left, right)

	int			m_CheckCountX;
	int			m_CheckCountY;

	int			m_CharLevel = 1;		// 0 : �⺻ĳ���� / 1 : ���� ���� ĳ���� / 2 : �� ���� ĳ����
	int			m_ObjectType = 0;		// 0 : �÷��̾� / 1 : ���� / 2 : ������
	bool		m_UseCollision;			// false : �浹ó������ ���� / true : �浹ó��
	DWORD		m_dwTime;
	DWORD		m_dieTime;
	DWORD		m_collTime;
	DWORD		m_collPauseTime;
	DWORD		m_tempPauseTime;
	DWORD		m_useDieTime;
	DWORD		m_useCollTime;
	DWORD		m_useCollPauseTime;
	DWORD		m_useTempPauseTime;
	DWORD		m_activeTime;

	int			m_wallBreakDir = 0;
	int			m_ItemType = 0;
	int			m_MonsterType = 0;

	bool		m_secure = 0;
	bool		m_secure2 = 0;
	int			m_lookLeftRight = 0;	// 1: ���� / 2: ������

protected:
	int			m_SpriteTime = 0; // ���� ��������Ʈ ������ ������
	int			m_SpriteXIndex = 0; // ���� ��������Ʈ �ε���(�׸��� �����ϴ� left ���� ��ǥ)
	int			m_SpriteYIndex = 0; // ���� ��������Ʈ �ε���(�׸��� �����ϴ� top ���� ��ǥ)
	int			m_SpriteStartIndex = 0; // �ִϸ��̼� ���� �ε���
	int			m_SpriteEndIndex = 0; // �ִϸ��̼� ���� �ε���
	DWORD		m_SpriteAnimTime = 0; // �ִϸ��̼� �ð��� üũ
	bool		m_SpriteX = 0; // ��������Ʈ �̹��� ���η�
	bool		m_SpriteY = 0; // ��������Ʈ �̹��� ���η�

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

	// �̹����� �� ���ϰ� �ҷ��������� ����� �Լ��Դϴ�.
	void		LoadImg(LPCWSTR Path, int width, int height);

	// ���� m_Image �� ����ִ��� üũ�ϴ� �޼ҵ�.
	// NULL true �� ��ȯ�մϴ�.
	bool		ImageNullCheck();

	void		Scroll();			// ȭ�� ��ũ��

	POINT GetScroll();

	virtual void Init()								PURE;
	virtual void Update()							PURE;
	virtual void Render(HDC memDC, HDC backMemDC)	PURE;

	void DieMotion();
	bool DieTimer();

	void MoveUpdate();
	void CollUpdate(int dir);
	void Direct(int dir);
	void EatItem(int level, int itemtype);
	void CollMonster(int level, int monstertype);
	
	void LevelUp();

	void SetSprite(int x, int y, int start, int end, int time);
	void SetCollInit(int w, int h, int usecoll, int speed);
	void SetImgSizeInit(int iw, int ih);

	int GetSpriteXIndex();
	int GetSpriteYIndex();
	int GetSpriteStartIndex();
	int GetSpriteEndIndex();

	void SetDieTime(DWORD time);
	void SetCollTime(DWORD time);
	void SetCollPauseTime(DWORD time);
	void SetTempPauseTime(DWORD time);

	void BaseUpdate();
	void BaseRender(HDC memDC, HDC backMemDC);
};

