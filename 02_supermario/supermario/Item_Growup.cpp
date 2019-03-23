#include "Item_Growup.h"
#include "CharacterManager.h"


Item_Growup::Item_Growup()
{
	Init();
}


Item_Growup::~Item_Growup()
{
}

void Item_Growup::Init()
{
	// ó�� �ʱ�ȭ�� �ؾ��� �͵�

	// �ش� ������Ʈ�� Ȱ��ȭ
	SetActive(true);

	// ������Ʈ ���� �׷��� �簢��Ȱ��ȭ
	SetShowRect(false);

	// �簢���� �׸��ٸ� Ÿ��Ʋ�� �׸� ������ ����
	SetDrawOnlyTitle(true);

	// ������Ʈ �̹��� �׸��� Ȱ��ȭ
	SetShowImage(true);

	// BMP �̹��� ��������
	LoadImg(L"mario_item.bmp", 0, 0);

	// �̹����� ������� ����� ������ ����
	m_UseTrasparent = true;

	// ���� ������ �����մϴ�.
	TransparentColor = RGB(255, 246, 0);
	//RGB(0, 0, 0);

	// ��������Ʈ �̹����� ����� ������ ����
	m_UseSprite = true;

	// �÷��̾��� �ʱ� ��ǥ�� ����
	//m_PosX = CharacterManager::GetPlayer()->m_PosX + 600;
	m_PosX = 0;
	m_PosY = 0;
	//m_PosY = 542;

	// ���� ������ ����, ���� ũ�� (�׷��� ũ��)
	m_Width = 36;
	m_Height = 36;

	// RECT�� ����ȭ
	UpdateRect();

	// ���� �̹��� ũ��
	m_ImgWidth = 16;
	m_ImgHeight = 16;

	m_CheckCountX = m_Width / MAP_TILE_SIZE;
	m_CheckCountY = m_Height / MAP_TILE_SIZE;

	// ��������Ʈ ������ �ʱ�ȭ�մϴ�.
	m_SpriteTime = 200; // 0.1��
	m_SpriteXIndex = 0;
	m_SpriteYIndex = 0;
	m_SpriteStartIndex = 0;
	m_SpriteEndIndex = 0;
	m_SpriteX = true;
	m_SpriteY = false;

	m_DirTopBottom = 0;
	m_DirLeftRight = 0;

	m_count			= 0;
	m_state			= 0;
	m_Gravity		= 0.0f;
	m_Speed			= 2.0f;				// ������ �� ���� �ӵ�
	m_MaxSpeed		= 6.0f;
	m_canLeft		= true;
	m_canRight		= false;

	m_ObjectType	= 2;
	m_UseCollision	= false;
	m_ItemType = 1;

	m_secure = false;

	m_dwTime = GetTickCount();
}

void Item_Growup::Update()
{
	MoveUpdate();

	Scroll();

	UpdateRect();

	BaseUpdate();
}

void Item_Growup::Render(HDC memDC, HDC backMemDC)
{
	BaseRender(memDC, backMemDC);
}

void Item_Growup::Scroll()
{
	m_Scroll = CharacterManager::GetPlayer()->GetScroll();
	/*if (CharacterManager::GetPlayer()->m_PosX < 200) {
		m_Scroll.x = m_passScroll.x;
	}
	else if (CharacterManager::GetPlayer()->m_PosX - 200 >= m_passScroll.x) {
		m_passScroll.x = CharacterManager::GetPlayer()->m_PosX - 200;
		m_Scroll.x = m_passScroll.x;
	}
	else {
		m_Scroll.x = m_passScroll.x;
	}*/
}

void Item_Growup::MoveUpdate()
{
	if (m_UseCollision) {
		// ����
		if (m_DirLeftRight == 1 && m_dwTime > 2000) {
			m_PosX -= m_Speed;
		}
		// ������
		else if (m_DirLeftRight == 0 && m_dwTime > 2000) {
			m_PosX += m_Speed;
		}
		m_dwTime = GetTickCount();

		if (m_Gravity > -40 && m_state == 1) {
			m_PosY -= m_Gravity;
			m_Gravity -= 1.0f;

			if (m_Gravity <= 0) {
				m_colDirTB = COL_BOTTOM;
			}
			else {
				m_colDirTB = COL_TOP;
			}
		}
		if (m_state == 0) {
			m_colDirTB = COL_NONE;
		}
	}
	else {
		m_PosY--;
		m_count++;

		if (m_count == 38) {
			m_UseCollision = true;
		}
	}
}
