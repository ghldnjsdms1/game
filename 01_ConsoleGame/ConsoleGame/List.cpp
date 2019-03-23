//#include "List.h"
//
//
//
//List::List()
//{
//}
//
//
//List::~List()
//{
//}
//
//void List::InitList(){
//	ListNode*	pFirstNode = new ListNode;
//	ListNode*	pSecondNode = new ListNode;
//
//	m_pBegin->m_pNext = pFirstNode;
//	pFirstNode->m_pNext = pSecondNode;
//	pSecondNode = m_pEnd;
//	pSecondNode->m_pNext = NULL;
//
//	pFirstNode->m_EW.m_dir = DIR_RIGHT;
//	pFirstNode->m_EW.m_posX = 6;
//	pFirstNode->m_EW.m_posY = 4;
//	pSecondNode->m_EW.m_dir = DIR_RIGHT;
//	pSecondNode->m_EW.m_posX = 4;
//	pSecondNode->m_EW.m_posY = 4;
//
//	m_iSize = 2;
//}
//
//void List::Push_Back(Earthwarm * pEW){
//	ListNode*	pNode = new ListNode;
//
//	pNode->m_pNext = NULL;
//	pNode->m_EW.m_posX = pEW->m_posX;
//	pNode->m_EW.m_posY = pEW->m_posY;
//
//	if (m_pBegin == NULL)
//		m_pBegin = pNode;
//	else
//		m_pEnd->m_pNext = pNode;
//	m_pEnd->m_pNext = pNode;
//
//	++m_iSize;
//}