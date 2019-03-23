#include "ScrollManager.h"
#include "CharacterManager.h"

ScrollManager::ScrollManager()
{
	POINT pt;

	pt.x = CharacterManager::GetPlayer()->m_PosX;
	pt.y = CharacterManager::GetPlayer()->m_PosY;

	m_prevPos.x += pt.x;
	m_prevPos.y = 0;
	m_Scroll.x = 0;
	m_Scroll.y = 0;
}


ScrollManager::~ScrollManager()
{
}

void ScrollManager::Update()
{
	POINT pt;

	pt.x = CharacterManager::GetPlayer()->m_PosX;
	pt.y = CharacterManager::GetPlayer()->m_PosY;

	//m_prevPos.x += pt.x;
	if (m_prevPos.x == pt.x) {
		m_Scroll.x = 0;
	}
	else if (m_prevPos.x != pt.x) {
		m_Scroll.x = pt.x - m_prevPos.x;
	}
}

POINT ScrollManager::GetScroll()
{
	return m_Scroll;
}
