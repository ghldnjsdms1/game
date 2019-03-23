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
	// 실제 보여질 타일 크기
	int			m_TileSize = 64;

	// 이미지 파일의 실제 크기
	int			m_OriTileSize = 128;

	POINT		m_ScreenSize;				// 화면 크기
	POINT		m_MapSize;					// 맵 크기(가로, 세로)
	POINT		m_ItemListSize;				// 아이템 리스트 크기

	HBITMAP		m_Image;					// 타일 시트 이미지
	DWORD		m_MapAcrossCount	= 8;	// 맵 타일 가로 최대 개수
	DWORD		m_MapMaxCount		= 32;	// 맵 타일 최대 개수

	DWORD		m_SelectNumber		= 0;	// 선택된 타일 인덱스 번호
	DWORD		m_AddNum			= 0;	// 아이템 리스트 이동변수

	DWORD		m_Map[100][100];			// 맵 타일
	DWORD		m_MapCollMap[100][100];		// 맵 충돌 타일
	bool		m_IsColl			= false;// 충돌타일 입력 활성화

	

public:


// Method__
private:


public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC memDC, HDC backMemDC);
	virtual void Destroy();

	// 이미지 편하게 불러오도록
	void		LoadImg(LPCWSTR path, int width, int height);

	// 맵 데이터를 모두 0으로 초기화
	void		InitMapData();

	// 맵 정보 불러오기
	void		LoadMap();

	// 맵 정보 저장
	void		SaveMap();
};

