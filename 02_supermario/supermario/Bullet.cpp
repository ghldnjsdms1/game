#include "Bullet.h"
#include "CharacterManager.h"


Bullet::Bullet()
{
	Init();
}


Bullet::~Bullet()
{
}

void Bullet::Init()
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
	//TransparentColor = NULL;
	//RGB(0, 0, 0);

	// ��������Ʈ �̹����� ����� ������ ����
	m_UseSprite = true;

	// �÷��̾��� �ʱ� ��ǥ�� ����
	m_PosX = 0;
	m_PosY = 0;

	// ���� ������ ����, ���� ũ�� (�׷��� ũ��)
	m_Width = 18;
	m_Height = 18;

	// RECT�� ����ȭ
	UpdateRect();

	// ���� �̹��� ũ��
	m_ImgWidth = 8;
	m_ImgHeight = 8;

	m_CheckCountX = 1;
	m_CheckCountY = 1;

	// ��������Ʈ ������ �ʱ�ȭ�մϴ�.
	m_SpriteTime = 50; // 0.1��
	m_SpriteXIndex = 12;
	m_SpriteYIndex = 18;
	m_SpriteStartIndex = 18;
	m_SpriteEndIndex = 21;
	m_SpriteX = false;
	m_SpriteY = true;

	m_DirTopBottom = 0;
	m_DirLeftRight = 0;

	m_count = 0;
	m_state = 0;
	m_Gravity = 0.0f;
	m_Speed = 9.0f;				// ������ �� ���� �ӵ�
	m_MaxSpeed = 6.0f;
	m_canLeft = true;
	m_canRight = false;

	m_ObjectType = 3;
	m_UseCollision = true;
	m_ItemType = 2;

	m_secure = false;
	m_chkColl = false;

	m_dwTime = GetTickCount();
}

void Bullet::Update()
{
	MoveUpdate();

	Scroll();

	UpdateRect();

	BaseUpdate();
}

void Bullet::Render(HDC memDC, HDC backMemDC)
{
	BaseRender(memDC, backMemDC);
}

void Bullet::Scroll()
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

void Bullet::SetPos(int x, int y, int dir)
{
	m_DirLeftRight = dir;
	switch (dir)
	{
	case 0:	// ������ ����
		m_PosX = x + 22;
		m_PosY = y;
		break;
	case 1:	// ���� ����
		m_PosX = x - 22;
		m_PosY = y;
		break;
	}
	UpdateRect();
}

void Bullet::UpdateRect()
{
	m_Rect = {
		m_PosX - (m_Width / 2),
		m_PosY - (m_Height / 2),
		m_PosX + (m_Width / 2),
		m_PosY + (m_Height / 2) };
}

void Bullet::MoveUpdate()
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

		if (m_Gravity > -40 && !m_chkColl) {
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
}

void Bullet::DieMotion()
{
}

