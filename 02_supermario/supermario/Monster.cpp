#include "Monster.h"
#include "CharacterManager.h"


Monster::Monster()
{
	this->Init();
}


Monster::~Monster()
{
	//if (m_Image != NULL) DeleteObject(m_Image);
}

void Monster::Init()
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
	LoadImg(L"mario_monster.bmp", 0, 0);
	
	// �̹����� ������� ����� ������ ����
	m_UseTrasparent = true;

	// ���� ������ �����մϴ�.
	TransparentColor = RGB(255, 246, 0);
	//RGB(0, 0, 0);

	// ��������Ʈ �̹����� ����� ������ ����
	m_UseSprite = true;

	// �÷��̾��� �ʱ� ��ǥ�� ����
	//m_PosX = CharacterManager::GetPlayer()->m_PosX + 600;
	m_PosX = 300;
	m_PosY = 300;
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
	m_SpriteEndIndex = 1;
	m_SpriteX = true;
	m_SpriteY = false;

	m_DirTopBottom = 0;
	m_DirLeftRight = 1;

	m_count			= 0;
	m_state			= 0;
	m_Gravity		= 0.0f;
	m_Speed			= 2.0f;				// ������ �� ���� �ӵ�
	m_MaxSpeed		= 6.0f;
	m_canLeft		= false;
	m_canRight		= true;

	m_ObjectType = 1;
	m_MonsterType = 1;
	m_UseCollision = true;

	m_secure = false;

	m_dwTime = GetTickCount();
}

void Monster::Update()
{
	MoveUpdate();

	Scroll();

	UpdateRect();

	BaseUpdate();
}

void Monster::Render(HDC memDC, HDC backMemDC)
{	
	//BaseRender(memDC, backMemDC);

	// ������Ʈ�� Ȱ��ȭ���̶��
	if (GetActive()) {
		// �簢���� �׸��� && Ÿ��Ʋ�� ����ϴ� ���̶��
		if (GetShowRect() && GetDrawOnlyTitle()) {
			Rectangle(backMemDC, m_Rect.left - m_Scroll.x, m_Rect.top, m_Rect.right - m_Scroll.x, m_Rect.bottom);
		}

		// �̹����� ��쵵�� �����ߴٸ�
		if (GetShowImage() && !ImageNullCheck()) {

			SelectObject(memDC, m_Image);

			// ��������Ʈ�� ������̶��
			if (m_UseSprite) {
				TransparentBlt(
					backMemDC,
					m_Rect.left - m_Scroll.x, m_Rect.top, m_Width, m_Height,
					memDC,
					m_SpriteXIndex == 0 ? (m_SpriteXIndex * m_ImgWidth) : m_SpriteXIndex * (m_ImgWidth + 14),
					(m_SpriteYIndex * m_ImgHeight) + 4,
					m_ImgWidth, m_ImgHeight,
					// ������� ������̶�� TransparentColor��, �ƴ϶�� NULL�� �־ ������� ������� �ʵ��� ����
					(m_UseTrasparent) ? TransparentColor : NULL);
			}
			// ��������Ʈ�� ������� �ƴ϶��
			else {
				TransparentBlt(
					backMemDC,
					m_Rect.left, m_Rect.top, m_Width, m_Height,
					memDC,
					0, 0, m_ImgWidth, m_ImgHeight,
					// ������� ������̶�� TransparentColor��, �ƴ϶�� NULL�� �־ ������� ������� �ʵ��� ����
					(m_UseTrasparent) ? TransparentColor : NULL);
			}

		}
		// �簢���� �׸��� && Ÿ��Ʋ�� ����ϴ°��� �ƴ϶��
		if (GetShowRect() && !GetDrawOnlyTitle()) {
			// ���������� �簢���� ĥ�մϴ�.
			FillRect(backMemDC, &m_Rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
	}
}

void Monster::Scroll()
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

void Monster::SetPos(int x, int y)
{
	//m_PosX = CharacterManager::GetPlayer()->m_PosX + 600;
	m_PosX = x + 600;
	m_PosY = 50;
}

void Monster::MoveUpdate()
{
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

void Monster::DieMotion(int type)
{
	switch (type)
	{
	case 0:
		SetSprite(2, 0, 2, 2, 500);
		SetCollInit(36, 36, false, m_Speed);
		SetImgSizeInit(16, 16);
		break;
	case 1:
		SetSprite(3, 0, 3, 3, 500);
		SetCollInit(36, 36, false, m_Speed);
		SetImgSizeInit(16, 16);
		break;
	}

	m_chkColl = true;
	m_CharLevel = 0;
	m_dieTime = GetTickCount();

	m_Gravity = 10.0f;
	m_state = 1;
}
