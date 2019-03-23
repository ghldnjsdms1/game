#include "GameUI.h"
#include "CharacterManager.h"


GameUI::GameUI()
{
	if (AddFontResourceA("emulogic.ttf"))
		Log("¼º°ø");
	
}


GameUI::~GameUI()
{
}

void GameUI::Init()
{
}

void GameUI::Update()
{
}

void GameUI::Render(HDC memDC, HDC backMemDC)
{
	TCHAR *str;
	HFONT font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Emulogic"));
	HFONT oldFont = (HFONT)SelectObject(backMemDC, font);
	SetBkMode(backMemDC, TRANSPARENT);
	SetTextColor(backMemDC, RGB(255, 255, 255));

	int i;
	TCHAR tChar[50] = { '\0', };

	str = TEXT("MARIO");
	TextOut(backMemDC, MAIN_WND_WIDTH / 16 * 2, 10, str, lstrlen(str));
	
	i = CharacterManager::GetPlayer()->m_totalScore;
	wsprintf(tChar, L"%d", i);
	TextOut(backMemDC, MAIN_WND_WIDTH / 16 * 2, 35, tChar, lstrlen(tChar));

	str = TEXT(" ");
	TextOut(backMemDC, MAIN_WND_WIDTH / 16 * 6, 10, str, lstrlen(str));
	str = TEXT("X");
	TextOut(backMemDC, MAIN_WND_WIDTH / 16 * 6, 35, str, lstrlen(str));
	i = CharacterManager::GetPlayer()->m_coinCount;
	wsprintf(tChar, L"%d", i);
	TextOut(backMemDC, MAIN_WND_WIDTH / 16 * 6 + 25, 35, tChar, lstrlen(tChar));

	str = TEXT("WORLD");
	TextOut(backMemDC, MAIN_WND_WIDTH / 16 * 9, 10, str, lstrlen(str));
	str = TEXT(" 1-1");
	TextOut(backMemDC, MAIN_WND_WIDTH / 16 * 9, 35, str, lstrlen(str));

	str = TEXT("TIME");
	TextOut(backMemDC, MAIN_WND_WIDTH / 16 * 12, 10, str, lstrlen(str));
	i = CharacterManager::GetPlayer()->m_liveTime;
	wsprintf(tChar, L"%d", i);
	TextOut(backMemDC, MAIN_WND_WIDTH / 16 * 12, 35, tChar, lstrlen(tChar));
	DeleteObject(font);
}
