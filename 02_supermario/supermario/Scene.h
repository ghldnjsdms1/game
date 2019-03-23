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

											
	int			m_TileSize = 40;			// 실제 보여질 타일 크기
	int			m_OriTileSize = 16;			// 이미지 파일의 실제 크기

	POINT		m_ScreenSize;				// 화면 크기
	POINT		m_MapSize;					// 맵 크기(가로, 세로)
	POINT		m_ItemListSize;				// 아이템 리스트 크기

	HBITMAP		m_Image = NULL;					// 타일 시트 이미지
	HBITMAP		m_ImageItem = NULL;				// 타일 아이템 이미지
	DWORD		m_MapAcrossCountX = 33;		// 맵 타일 가로 최대 개수
	DWORD		m_MapAcrossCountY = 28;		// 맵 타일 세로 최대 개수
	DWORD		m_MapAcrossCount= 20;		// 맵 타일 세로 최대 개수
	DWORD		m_MapMaxCount = 924;		// 맵 타일 최대 개수

	POINT		m_SelectNumber_;
	DWORD		m_SelectNumber = 0;			// 선택된 타일 인덱스 번호
	DWORD		m_AddNum = 0;				// 아이템 리스트 이동변수

	DWORD		m_Map[256][256];			// 맵 타일
	DWORD		m_MapCollMap[256][256];		// 맵 충돌 타일

	// 타일 종류 - 0:길 / 1:깨지지않는벽 / 2:깨지는벽 / 3:동전아이템타일 / 4:버섯,꽃아이템타일 / 5:별아이템타일
	int			m_IsColl = 0;			// 충돌타일 입력 활성화
	bool		m_IsRect = true;			// 타일 사각형 활성화

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
	int			m_SpriteTime = 0;			// 현재 스프라이트 프레임 딜레이
	int			m_SpriteXIndex = 0;			// 현재 스프라이트 인덱스(그리기 시작하는 left 시작 좌표)
	int			m_SpriteYIndex = 0;			// 현재 스프라이트 인덱스(그리기 시작하는 top 시작 좌표)
	int			m_SpriteStartIndex = 0;		// 애니메이션 시작 인덱스
	int			m_SpriteEndIndex = 0;		// 애니메이션 종료 인덱스
	DWORD		m_SpriteAnimTime = 0;		// 애니메이션 시간을 체크

// Method__
private:


public:
	virtual void Init()											PURE;
	virtual void Update()										PURE;
	virtual void Render(HDC memDC, HDC backMemDC)				PURE;
	virtual void Destroy()										PURE;

	virtual void LoadImg(LPCWSTR path, int width, int height)	PURE;	// 이미지 편하게 불러오도록
	virtual void InitMapData()									PURE;	// 맵 데이터를 모두 0으로 초기화
	virtual void LoadMap()										PURE;	// 맵 정보 불러오기
	virtual void SaveMap()										PURE;	// 맵 정보 저장
	
	void Pause();
	void ScreenExcept(Object* object, list<Object*>* objectList);

	void BaseUpdate();
	void BaseRender(HDC memDC, HDC backMemDC);
};

