#pragma once
#include "Scene.h"
#include <fstream>

class FirstScene : public Scene
{
public:
	FirstScene();
	virtual ~FirstScene();

// Variable__
private:
	// ���� ������ Ÿ�� ũ��
	int			m_TileSize = 64;

	// �̹��� ������ ���� ũ��
	int			m_OriTileSize = 128;

	POINT		m_ScreenSize;				// ȭ�� ũ��
	POINT		m_MapSize;					// �� ũ��(����, ����)
	POINT		m_ItemListSize;				// ������ ����Ʈ ũ��

	HBITMAP		m_Image;					// Ÿ�� ��Ʈ �̹���
	DWORD		m_MapAcrossCount	= 8;	// �� Ÿ�� ���� �ִ� ����
	DWORD		m_MapMaxCount		= 32;	// �� Ÿ�� �ִ� ����

	DWORD		m_SelectNumber		= 0;	// ���õ� Ÿ�� �ε��� ��ȣ
	DWORD		m_AddNum			= 0;	// ������ ����Ʈ �̵�����

	DWORD		m_Map[100][100];			// �� Ÿ��
	DWORD		m_MapCollMap[100][100];		// �� �浹 Ÿ��
	bool		m_IsColl			= false;// �浹Ÿ�� �Է� Ȱ��ȭ

	

public:


// Method__
private:


public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC memDC, HDC backMemDC);
	virtual void Destroy();

	// �̹��� ���ϰ� �ҷ�������
	void		LoadImg(LPCWSTR path, int width, int height);

	// �� �����͸� ��� 0���� �ʱ�ȭ
	void		InitMapData();

	// �� ���� �ҷ�����
	void		LoadMap();

	// �� ���� ����
	void		SaveMap();
};

