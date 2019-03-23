#pragma once
#include "Scene.h"
#include <fstream>
#include "CharacterManager.h"

class MakeScene : public Scene
{
public:
	MakeScene();
	virtual ~MakeScene();

	// Variable__
private:
	//// ���� ������ Ÿ�� ũ��
	//int			m_TileSize = 32;

	//// �̹��� ������ ���� ũ��
	//int			m_OriTileSize = 16;

	//POINT		m_ScreenSize;				// ȭ�� ũ��
	//POINT		m_MapSize;					// �� ũ��(����, ����)
	//POINT		m_ItemListSize;				// ������ ����Ʈ ũ��

	//HBITMAP		m_Image;					// Ÿ�� ��Ʈ �̹���
	//DWORD		m_MapAcrossCountX	= 33;	// �� Ÿ�� ���� �ִ� ����
	//DWORD		m_MapAcrossCountY	= 28;	// �� Ÿ�� ���� �ִ� ����
	//DWORD		m_MapAcrossCount	= 20;	// �� Ÿ�� ���� �ִ� ����
	//DWORD		m_MapMaxCount		= 924;	// �� Ÿ�� �ִ� ����

	//POINT		m_SelectNumber_;
	//DWORD		m_SelectNumber = 0;			// ���õ� Ÿ�� �ε��� ��ȣ
	//DWORD		m_AddNum = 0;				// ������ ����Ʈ �̵�����

	//DWORD		m_Map[100][100];			// �� Ÿ��
	//DWORD		m_MapCollMap[100][100];		// �� �浹 Ÿ��
	//bool		m_IsColl = false;			// �浹Ÿ�� �Է� Ȱ��ȭ
	//bool		m_IsRect = true;			// Ÿ�� �簢�� Ȱ��ȭ

	//POINT		m_Scroll;

public:
	Player * m_pPlayer;

	// Method__
private:


public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC memDC, HDC backMemDC);
	virtual void Destroy();

	// �̹��� ���ϰ� �ҷ�������
	virtual void		LoadImg(LPCWSTR path, int width, int height);

	// �� �����͸� ��� 0���� �ʱ�ȭ
	virtual void		InitMapData();

	// �� ���� �ҷ�����
	virtual void		LoadMap();

	// �� ���� ����
	virtual void		SaveMap();
};

