#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Pause()
{
	if (GetAsyncKeyState(VK_ESCAPE) && GetTickCount() - m_keyTime > 100)
	{
		m_keyTime = GetTickCount();

		m_gamePause = !m_gamePause;
	}
}

void Scene::ScreenExcept(Object * object, list<Object*>* objectList)
{
	POINT scroll = object->GetScroll();

	list<Object*>::iterator	iter;
	iter = objectList->begin();
	for (; iter != objectList->end(); iter++) {
		if ((*iter)->m_PosX < scroll.x - 200 || (*iter)->m_PosX > scroll.x + MAIN_WND_WIDTH + 200) {
			delete *iter;
			objectList->erase(iter);
			break;
		}
	}
}

void Scene::BaseUpdate()
{
	// 만약 지정한 스프라이트 딜레이가 지난다면
	if (GetTickCount() - m_SpriteAnimTime > m_SpriteTime && m_SpriteXIndex != m_SpriteStartIndex) {
		m_SpriteAnimTime = GetTickCount();
		m_SpriteXIndex++;

		m_SpriteXIndex = (m_SpriteXIndex > m_SpriteEndIndex) ? m_SpriteStartIndex : m_SpriteXIndex;
	}
	else if (GetTickCount() - m_SpriteAnimTime > (m_SpriteTime * 2) && m_SpriteXIndex == m_SpriteStartIndex) {
		m_SpriteAnimTime = GetTickCount();
		m_SpriteXIndex++;

		m_SpriteXIndex = (m_SpriteXIndex > m_SpriteEndIndex) ? m_SpriteStartIndex : m_SpriteXIndex;
	}
}

void Scene::BaseRender(HDC memDC, HDC backMemDC)
{
	// 맵 타일 그리기
	for (int i = 0; i < m_MapSize.y; ++i) {
		for (int j = 0; j < m_MapSize.x; ++j) {
			SelectObject(memDC, m_Image);

			if (m_Map[i][j] % m_MapAcrossCountX == 24 && (m_Map[i][j] / m_MapAcrossCountX) % 2 == 0 && m_Map[i][j] / m_MapAcrossCountX < 8) {
				TransparentBlt(
					backMemDC,
					m_TileSize * j - m_Scroll.x, m_TileSize * i, m_TileSize, m_TileSize,
					memDC,
					((m_Map[i][j] % m_MapAcrossCountX) * m_OriTileSize) + (m_SpriteXIndex * m_OriTileSize),
					(m_Map[i][j] / m_MapAcrossCountX) * m_OriTileSize + (m_SpriteYIndex * m_OriTileSize),
					m_OriTileSize, m_OriTileSize, RGB(255, 246, 0));
			}
			else {
				TransparentBlt(
					backMemDC,
					m_TileSize * j - m_Scroll.x, m_TileSize * i, m_TileSize, m_TileSize,
					memDC,
					(m_Map[i][j] % m_MapAcrossCountX) * m_OriTileSize,
					(m_Map[i][j] / m_MapAcrossCountX) * m_OriTileSize,
					m_OriTileSize, m_OriTileSize, RGB(255, 246, 0));
			}

		}
	}
}
