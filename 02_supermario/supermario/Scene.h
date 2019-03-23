#pragma once
#include "WndDefine.h"
#include "Object.h"
#include <list>

class Scene
{
public:
	Scene();
	virtual ~Scene();

// Variable__
private:


public:
	RECT		m_FillRect = { 0, 0, MAIN_WND_WIDTH, MAIN_WND_HEIGHT };

											
	int			m_TileSize = 40;			// ���� ������ Ÿ�� ũ��
	int			m_OriTileSize = 16;			// �̹��� ������ ���� ũ��

	POINT		m_ScreenSize;				// ȭ�� ũ��
	POINT		m_MapSize;					// �� ũ��(����, ����)
	POINT		m_ItemListSize;				// ������ ����Ʈ ũ��

	HBITMAP		m_Image = NULL;					// Ÿ�� ��Ʈ �̹���
	HBITMAP		m_ImageItem = NULL;				// Ÿ�� ������ �̹���
	DWORD		m_MapAcrossCountX = 33;		// �� Ÿ�� ���� �ִ� ����
	DWORD		m_MapAcrossCountY = 28;		// �� Ÿ�� ���� �ִ� ����
	DWORD		m_MapAcrossCount= 20;		// �� Ÿ�� ���� �ִ� ����
	DWORD		m_MapMaxCount = 924;		// �� Ÿ�� �ִ� ����

	POINT		m_SelectNumber_;
	DWORD		m_SelectNumber = 0;			// ���õ� Ÿ�� �ε��� ��ȣ
	DWORD		m_AddNum = 0;				// ������ ����Ʈ �̵�����

	DWORD		m_Map[256][256];			// �� Ÿ��
	DWORD		m_MapCollMap[256][256];		// �� �浹 Ÿ��

	// Ÿ�� ���� - 0:�� / 1:�������ʴº� / 2:�����º� / 3:����������Ÿ�� / 4:����,�ɾ�����Ÿ�� / 5:��������Ÿ��
	int			m_IsColl = 0;			// �浹Ÿ�� �Է� Ȱ��ȭ
	bool		m_IsRect = true;			// Ÿ�� �簢�� Ȱ��ȭ

	POINT		m_Scroll;

	DWORD*		m_pCollMap;			// 


	enum OBJECT_TYPE
	{
		MONSTER1, MONSTER2, 
		ITEM_COIN, ITEM_GROWUP1, ITEM_GROWUP2, ITEM_STAR, ITEM_WALLBREAK
	};
	enum WALL_TYPE {
		WALL_NONE,
		WALL_DONT_BREAK,
		WALL_BREAK,
		WALL_ITEM_COIN,
		WALL_ITEM_GROWUP,
		WALL_ITEM_STAR
	};
	WALL_TYPE	m_wallType;
	bool		m_wallState;
	int			m_wallCount;

	bool		m_gamePause;
	DWORD		m_keyTime;

	POINT		m_charPos;
	int			m_monsterMakeCnt;
	bool		m_monsterCheck[100] = { false, };

protected:
	int			m_SpriteTime = 0;			// ���� ��������Ʈ ������ ������
	int			m_SpriteXIndex = 0;			// ���� ��������Ʈ �ε���(�׸��� �����ϴ� left ���� ��ǥ)
	int			m_SpriteYIndex = 0;			// ���� ��������Ʈ �ε���(�׸��� �����ϴ� top ���� ��ǥ)
	int			m_SpriteStartIndex = 0;		// �ִϸ��̼� ���� �ε���
	int			m_SpriteEndIndex = 0;		// �ִϸ��̼� ���� �ε���
	DWORD		m_SpriteAnimTime = 0;		// �ִϸ��̼� �ð��� üũ

// Method__
private:


public:
	virtual void Init()											PURE;
	virtual void Update()										PURE;
	virtual void Render(HDC memDC, HDC backMemDC)				PURE;
	virtual void Destroy()										PURE;

	virtual void LoadImg(LPCWSTR path, int width, int height)	PURE;	// �̹��� ���ϰ� �ҷ�������
	virtual void InitMapData()									PURE;	// �� �����͸� ��� 0���� �ʱ�ȭ
	virtual void LoadMap()										PURE;	// �� ���� �ҷ�����
	virtual void SaveMap()										PURE;	// �� ���� ����
	
	void Pause();
	void ScreenExcept(Object* object, list<Object*>* objectList);

	void BaseUpdate();
	void BaseRender(HDC memDC, HDC backMemDC);
};

