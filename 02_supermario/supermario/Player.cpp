#include "Player.h"
#include "GameManager.h"

Player::Player()
{
	this->Init();
}


Player::~Player()
{
	for (auto it = m_BulletList.begin(); it != m_BulletList.end(); it++) {
		delete *it;
	}
}

void Player::InputKey()
{
	if ((GetAsyncKeyState('X')) && m_preFlag == true) {
		m_flag = true;
	}
	else {
		if (m_flag)
			m_flag = false;
	}
	
	if ((GetAsyncKeyState('X')) && m_state == 0 && m_flag == false) {
		m_cnt = 0;
		m_state = 1;
		m_Gravity = m_NormalGravity;
		Log("����!");
		
		switch (m_CharLevel)
		{
		case 0:
			switch (m_DirLeftRight)
			{
			case 0:
				SetSprite(26, 2, 26, 26, m_SpriteTime);
				break;
			case 1:
				SetSprite(15, 2, 15, 15, m_SpriteTime);
				break;
			}
			break;
		case 1:
			switch (m_DirLeftRight)
			{
			case 0:
				SetSprite(26, 0, 26, 26, m_SpriteTime);
				break;
			case 1:
				SetSprite(15, 0, 15, 15, m_SpriteTime);
				break;
			}
			break;
		case 2:
			switch (m_DirLeftRight)
			{
			case 0:
				SetSprite(26, 3, 26, 26, m_SpriteTime);
				break;
			case 1:
				SetSprite(15, 3, 15, 15, m_SpriteTime);
				break;
			}
			break;
		}

		m_DirTopBottom = COL_TOP;
	}

	if ((!GetAsyncKeyState('X') && m_preFlag && !m_flag) || (m_cnt >= 20)) {
		m_cnt = 10;
	}
	
	if ((GetAsyncKeyState('X'))) {
		if (!m_preFlag)	m_preFlag = true;
		
		if (m_cnt < 20) {
			m_cnt++;
			if (m_Gravity > 0) {
				if (!GetAsyncKeyState('Z'))
					m_Gravity += m_AccelGravity;
				else
					m_Gravity += m_AccelGravity + m_AccelSpeed - 0.10f;
			}
		}
	}
	else {
		m_preFlag = false;
	}	
	
	//Ű �Է��� �ִٸ�
	if (GetAsyncKeyState(VK_LEFT) ||
		GetAsyncKeyState(VK_RIGHT) ||
		GetAsyncKeyState(VK_UP) ||
		GetAsyncKeyState(VK_DOWN))
	{
		// Ű�Է� �ѹ����ް� : & 0x0001
		if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState('Z') && m_Rect.left > 0) {
			if (m_Dir != Direction::LEFT || m_Ac != Action::MOVE)
			{
				m_Ac = Action::MOVE;
				m_Dir = Direction::LEFT;
				m_DirLeftRight = 1;
				switch (m_CharLevel)
				{
				case 0:
					SetSprite(17, 2, 17, 19, m_SpriteTime);
					break;
				case 1:
					SetSprite(17, 0, 17, 19, m_SpriteTime);
					break;
				case 2:
					SetSprite(17, 3, 17, 19, m_SpriteTime);
					break;
				}
			}			

			if (m_Scroll.x < m_Rect.left) {
				if (m_canLeft)		m_PosX += m_Speed;
				else				m_Speed = m_MinSpeed;

				if (!m_canRight)	m_canRight = true;

				if (m_Speed < -m_NormalSpeed) {
					m_Speed += m_AccelSpeed;
					if (m_Speed > -m_NormalSpeed) {
						m_Speed = -m_NormalSpeed;
					}
				}
				else if (m_Speed > -m_NormalSpeed) {
					if (m_Speed <= 0) {
						m_Speed -= m_AccelSpeed;
					}
					else if (m_Speed > 0) {
						m_Speed -= m_AccelSpeed * 3;
						if (!m_canLeft) m_Speed = 0;
					}

					if (m_Speed < -m_NormalSpeed) {
						m_Speed = -m_NormalSpeed;
					}
				}
			}
			else {
				m_Speed = m_MinSpeed;
				m_PosX = m_Scroll.x + m_Width / 2;
				UpdateRect();
				m_canLeft = false;
			}
			m_colDirLR = COL_LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState('Z')) {
			if (m_Dir != Direction::RIGHT || m_Ac != Action::MOVE)
			{
				m_Ac = Action::MOVE;
				m_Dir = Direction::RIGHT;
				m_DirLeftRight = 0;
				switch (m_CharLevel)
				{
				case 0:
					SetSprite(22, 2, 22, 24, m_SpriteTime);
					break;
				case 1:
					SetSprite(22, 0, 22, 24, m_SpriteTime);
					break;
				case 2:
					SetSprite(22, 3, 22, 24, m_SpriteTime);
					break;
				}
			}

			if (m_canRight)		m_PosX += m_Speed;
			else				m_Speed = m_MinSpeed;

			if (!m_canLeft)		m_canLeft = true;

			if (m_Speed < m_NormalSpeed) {
				if (m_Speed >= 0)
					m_Speed += m_AccelSpeed;
				else {
					m_Speed += m_AccelSpeed * 3;
					if (!m_canRight) m_Speed = 0;
				}

				if (m_Speed > m_NormalSpeed)
					m_Speed = m_NormalSpeed;
			}
			else if (m_Speed > m_NormalSpeed) {
				m_Speed -= m_AccelSpeed;

				if (m_Speed < m_NormalSpeed)
					m_Speed = m_NormalSpeed;
			}
			
			m_colDirLR = COL_RIGHT;
		}
		/*else {
			m_Speed = m_MinSpeed;
			m_PosX = m_Scroll.x + m_Width / 2;
			UpdateRect();
		}*/
		if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState('Z') && m_Rect.left > 0) {
			if (m_Dir != Direction::LEFT || m_Ac != Action::MOVE)
			{
				m_Ac = Action::MOVE;
				m_Dir = Direction::LEFT;
				m_DirLeftRight = 1;
				switch (m_CharLevel)
				{
				case 0:
					SetSprite(17, 2, 17, 19, m_SpriteTime);
					break;
				case 1:
					SetSprite(17, 0, 17, 19, m_SpriteTime);
					break;
				case 2:
					SetSprite(17, 3, 17, 19, m_SpriteTime);
					break;
				}
			}
			
			if (m_Scroll.x < m_Rect.left) {
				if (m_canLeft)		m_PosX += m_Speed;
				else				m_Speed = m_MinSpeed;
				if (!m_canRight)	m_canRight = true;

				if (m_Speed < -m_MaxSpeed) {
					m_Speed = -m_MaxSpeed;
				}
				else if (m_Speed > -m_MaxSpeed) {
					if (m_Speed <= 0)
						m_Speed -= m_AccelSpeed;
					else
						m_Speed -= m_AccelSpeed * 3;
				}
			}
			else {
				m_Speed = m_MinSpeed;
				m_PosX = m_Scroll.x + m_Width / 2;
				UpdateRect();
				m_canLeft = false;
			}
			m_colDirLR = COL_LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState('Z')) {
			if (m_Dir != Direction::RIGHT || m_Ac != Action::MOVE)
			{
				m_Ac = Action::MOVE;
				m_Dir = Direction::RIGHT;
				m_DirLeftRight = 0;
				switch (m_CharLevel)
				{
				case 0:
					SetSprite(22, 2, 22, 24, m_SpriteTime);
					break;
				case 1:
					SetSprite(22, 0, 22, 24, m_SpriteTime);
					break;
				case 2:
					SetSprite(22, 3, 22, 24, m_SpriteTime);
					break;
				}
			}
			
			if (m_canRight)		m_PosX += m_Speed;
			else				m_Speed = m_MinSpeed;
			if (!m_canLeft)		m_canLeft = true;

			if (m_Speed > m_MaxSpeed) {
				m_Speed = m_MaxSpeed;
			}
			else if (m_Speed < m_MaxSpeed) {
				if (m_Speed >= 0)
					m_Speed += m_AccelSpeed;
				else
					m_Speed += m_AccelSpeed * 5;
			}

			m_colDirLR = COL_RIGHT;
		}
		/*else if (m_PosX < m_Scroll.x) {
			m_Speed = m_MinSpeed;
			m_PosX = m_Scroll.x + m_Width / 2;
			UpdateRect();
			m_canLeft = false;
		}*/
		
		//////////////////
		else if (GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT)) {
			if (m_Dir != Direction::UP || m_Ac != Action::MOVE)
			{
				m_Ac = Action::MOVE;
				m_Dir = Direction::UP;
				switch (m_CharLevel)
				{
				case 0:
					if (m_DirLeftRight == 0) {
						SetSprite(21, 2, 21, 21, m_SpriteTime);
					}
					else {
						SetSprite(20, 2, 20, 20, m_SpriteTime);
					}
					break;
				case 1:
					break;
				case 2:
					break;
				}
			}
		}
		else if (GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT)) {
			if (m_Dir != Direction::DOWN || m_Ac != Action::MOVE)
			{
				m_Ac = Action::MOVE;
				//m_Dir = Direction::DOWN;
				switch (m_CharLevel)
				{
				case 0:
					if (m_DirLeftRight == 0) {
						SetSprite(21, 2, 21, 21, m_SpriteTime);
					}
					else {
						SetSprite(20, 2, 20, 20, m_SpriteTime);
					}
					break;
				case 1:
					if (m_DirLeftRight == 0) {
						SetSprite(27, 0, 27, 27, m_SpriteTime);
					}
					else {
						SetSprite(14, 0, 14, 14, m_SpriteTime);
					}
					break;
				case 2:
					break;
				}
			}

			if (m_Speed > m_MinSpeed) {
				m_Speed -= m_AccelSpeed;
				if (m_Speed <= m_MinSpeed)
					m_Speed = m_MinSpeed;

				if (m_canRight)		m_PosX += m_Speed;
			}
			else if (m_Speed < m_MinSpeed) {
				m_Speed += m_AccelSpeed;
				if (m_Speed >= m_MinSpeed)
					m_Speed = m_MinSpeed;

				if (m_canLeft)		m_PosX += m_Speed;
			}

			switch (m_DirLeftRight)
			{
			case 0:	// ������
				break;
			case 1:	// ����
				break;
			}
		}
	}
	else {
		if(m_Speed > m_MinSpeed) {
			m_Speed -= m_AccelSpeed;
			if (m_Speed <= m_MinSpeed)
				m_Speed = m_MinSpeed;

			if (m_canRight)		m_PosX += m_Speed;
		}
		else if (m_Speed < m_MinSpeed) {
			if (m_Scroll.x < m_Rect.left) {
				m_Speed += m_AccelSpeed;
				if (m_Speed >= m_MinSpeed)
					m_Speed = m_MinSpeed;

				if (m_canLeft)		m_PosX += m_Speed;
			}
			else {
				m_PosX = m_Scroll.x + m_Width / 2;
				m_Speed = 0;
			}
		}
		if (m_Ac != Action::IDLE) {
			m_Ac = Action::IDLE;
		}
		
		switch (m_Dir) {
		case Direction::UP:
			/*m_SpriteYIndex = 3;
			m_SpriteStartIndex = 1;
			m_SpriteEndIndex = 1;*/
			break;
		case Direction::DOWN:
			switch (m_CharLevel)
			{
			case 0:
				if (m_DirLeftRight == 0) {
					SetSprite(21, 2, 21, 21, m_SpriteTime);
				}
				else {
					SetSprite(20, 2, 20, 20, m_SpriteTime);
				}
				break;
			case 1:
				if (m_DirLeftRight == 0) {
					SetSprite(27, 0, 27, 27, m_SpriteTime);
				}
				else {
					SetSprite(14, 0, 14, 14, m_SpriteTime);
				}
				break;
			case 2:
				break;
			}
			break;
		case Direction::LEFT:
			switch (m_CharLevel)
			{
			case 0:
				SetSprite(20, 2, 20, 20, m_SpriteTime);
				break;
			case 1:
				SetSprite(20, 0, 20, 20, m_SpriteTime);
				break;
			case 2:
				SetSprite(20, 3, 20, 20, m_SpriteTime);
				break;
			}
			break;
		case Direction::RIGHT:
			switch (m_CharLevel)
			{
			case 0:
				SetSprite(21, 2, 21, 21, m_SpriteTime);
				break;
			case 1:
				SetSprite(21, 0, 21, 21, m_SpriteTime);
				break;
			case 2:
				SetSprite(21, 3, 21, 21, m_SpriteTime);
				break;
			}
			break;
		}
	}

	if (m_keyZState == KEY_RELEASE && GetAsyncKeyState('Z') && m_CharLevel == 2) {
		m_keyZState = KEY_PRESSED;
		if (m_BulletList.size() < 2) {
			m_BulletList.push_back(new Bullet);
			iter = m_BulletList.end();
			iter--;
			switch (m_DirLeftRight)
			{
			case 0:		// ������ ����
				(*iter)->m_DirLeftRight = 0;
				break;
			case 1:		// ���� ����
				(*iter)->m_DirLeftRight = 1;
				break;
			}
			dynamic_cast<Bullet*>(*iter)->SetPos(m_PosX, m_PosY, m_DirLeftRight);
		}
	}
	else if (!GetAsyncKeyState('Z')) {
		if(m_keyZState != KEY_RELEASE) m_keyZState = KEY_RELEASE;
	}
}

void Player::DieMotion()
{
}

bool Player::DontCollision()
{
	if (GetTickCount() - m_collTime > m_useCollTime) {
		m_UseCollision = true;
		if (!GetActive())
			SetActive(true);
		return true;
	}
	else if (!m_UseCollision) {
		if (GetTickCount() - m_activeTime > 50) {
			m_activeTime = GetTickCount();
			if (GetActive())
				SetActive(false);
			else
				SetActive(true);
		}
	}
	return false;
}

bool Player::CollPauseTime()
{
	if (GetTickCount() - m_collPauseTime > m_useCollPauseTime) {
		m_collPause = false;

		if (m_clearScene) {
			m_clearScene = false;

			if (m_currentScene == SCENE_PLAY) {
				GameManager::GetGameManager()->GetSceneManager()->ChangeScene("GameOverScene");
				GameManager::GetGameManager()->GetSceneManager()->DestroyScene("PlayScene");
			}
		}		
		return true;
	}
	else if (!m_secure && m_CharLevel > -1 && !m_clearScene) {
		m_PosY--;
		m_life--;
	}
	return false;
}

bool Player::TempPause()
{
	if (GetTickCount() - m_tempPauseTime > m_useTempPauseTime) {
		m_tempPause = false;
		m_SpriteX = true;
		m_SpriteY = false;

		switch (m_secure2)
		{
		case 0:
			break;
		case 1:
			switch (m_CharLevel)
			{
			case 0:
				//SetSprite(m_SpriteXIndex, 2, m_SpriteStartIndex, m_SpriteEndIndex, 100);
				SetCollInit(m_Width, m_Height / 2, false, m_Speed);
				SetImgSizeInit(m_ImgWidth, m_ImgHeight / 2);
				m_PosY = m_PosY + m_Height / 2;
				break;
			case 1:
				break;
			case 2:
				break;
			}
			break;
		}
		return true;
	}
	return false;
}

void Player::ClearScene()
{
	switch (m_CharLevel)
	{
	case 0:
		// ���� �����
		SetSprite(21, 2, 21, 23, m_SpriteTime);
		m_PosX = 7978;
		m_PosY = 462;
		break;
	case 1: 
		SetSprite(21, 0, 21, 23, m_SpriteTime);
		m_PosX = 7978;
		m_PosY = 444;
		break;
	case 2:
		SetSprite(21, 3, 21, 23, m_SpriteTime);
		m_PosX = 7978;
		m_PosY = 444;
		break;
	}
	//m_UseCollision		= false;
	
	m_clearScene = true;
	SetCollTime(3000);
	SetCollPauseTime(3000);
	SetTempPauseTime(3000);
	m_tempPause = true;
	m_collPause = true;
	m_tempPauseTime = GetTickCount();
	m_collTime = GetTickCount();
	m_collPauseTime = GetTickCount();
	UpdateRect();
}

void Player::Init()
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
	LoadImg(L"mario_char.bmp", 0, 0);
	
	// �̹����� ������� ����� ������ ����
	m_UseTrasparent = true;

	// ���� ������ �����մϴ�.
	TransparentColor = RGB(255, 246, 0);
	//RGB(0, 0, 0);

	// ��������Ʈ �̹����� ����� ������ ����
	m_UseSprite = true;

	// �÷��̾��� �ʱ� ��ǥ�� ����
	m_PosX = 200;
	m_PosY = 200;

	// ���� �÷��̾��� ����, ���� ũ�� (�׷��� ũ��)
	m_Width = 36;
	m_Height = 36;

	// RECT�� ����ȭ
	UpdateRect();

	// �÷��̾� �̹��� ũ��
	m_ImgWidth = 16;
	m_ImgHeight = 16;

	// ��������Ʈ ������ �ʱ�ȭ�մϴ�.
	m_SpriteTime = 100; // 0.1��
	m_SpriteXIndex = 21;
	m_SpriteYIndex = 2;
	m_SpriteStartIndex = 21;
	m_SpriteEndIndex = 21;
	m_SpriteX = true;
	m_SpriteY = false;

	m_life = 2;
	m_coinCount = 0;
	m_totalScore = 0;
	m_liveTime = 200;
	m_liveTimeCount = 0;

	m_CheckCountX = m_Width / MAP_TILE_SIZE;
	m_CheckCountY = m_Height / MAP_TILE_SIZE;

	m_DirTopBottom	= 0;
	m_DirLeftRight	= 0;

	m_count			= 0;
	m_state			= 0;
	m_MaxGravity	= 18.0f;
	m_NormalGravity = 12.0f;
	m_Gravity		= 0.0f;
	m_AccelMaxGravity = 5.0f;
	m_AccelGravity	= 0.5f;
	m_MaxSpeed		= 6.0f;
	m_MinSpeed		= 0.0f;
	m_NormalSpeed	= 4.0f;
	m_Speed			= m_MinSpeed;				// ������ �� ���� �ӵ�
	m_AccelSpeed	= 0.15f;
	m_canLeft		= true;
	m_canRight		= true;
	m_flag			= false;
	m_preFlag		= false;
	m_keyJumpFlag	= false;

	m_ObjectType	= 0;
	m_CharLevel		= 0;

	m_secure		= true;
	m_secure2		= true;
	m_lookLeftRight = 2;
	m_Dir = Direction::RIGHT;

	m_dwTime = GetTickCount();
	m_activeTime = GetTickCount();

	m_colDirTB = COL_BOTTOM;		// ���� �浹 ���� (top, bottom)
	m_colDirLR = COL_NONE;			// ���� �浹 ���� (left, right)

	m_cnt = 0;
	m_UseCollision = true;
	m_clearScene = false;

	m_flagZ = false;
	m_keyZState = KEY_RELEASE;

	ScrollInit(0, 0);
}

void Player::Update()
{
	if (!m_collPause) {
		InputKey();

		MoveUpdate();

		Scroll();

		UpdateRect();

		iter = m_BulletList.begin();
		for (; iter != m_BulletList.end(); iter++) {
			(*iter)->Update();
		}
	}
	else if (m_CharLevel == -1 && !m_tempPause) {
		m_life--;

		MoveUpdate();

		Scroll();

		UpdateRect();
	}
	else {
		TempPause();
	}

	if (m_clearScene)
		m_PosX++;

	LiveTime();

	BaseUpdate();
}

void Player::Render(HDC memDC, HDC backMemDC)
{
	BaseRender(memDC, backMemDC);
	
	iter = m_BulletList.begin();
	for (; iter != m_BulletList.end(); iter++) {
		(*iter)->Render(memDC, backMemDC);
	}

	/*BitBlt(backMemDC,
	m_Rect.left,
	m_Rect.top,
	m_Width,
	m_Height,
	memDC, 0, 0, SRCCOPY);*/

	// TransparentBlt : ��Ʈ���� �Ϻθ� �����ϰ� ó�����ִ� �Լ�
	//					�ش� �Լ��� msimg32.lib�����ԵǾ��ֱ� ������ �� ������ ������Ʈ�� ���ӽ��Ѿ�
	//					����� �� �ֽ��ϴ�.
	// 1	: ��¿� DC
	// 2, 3	: �̹����� ����ϱ� ������ x,y ��ǥ
	// 4, 5 : ����������� ������� width, height
	// 6	: ������ ������ ������ DC
	// 7, 8, 9, 10 : �޸𸮿��� ������ �簢���� ����
	// 11	: �����ϰ� ó���� ����
}

void Player::SetPos(int x, int y)
{
	m_PosX = x;
	m_PosY = y;
}

void Player::SetScene(CURRENT_SCENE scene)
{
	m_currentScene = scene;
}

void Player::SceneInit(CURRENT_SCENE scene, int x, int y, bool scroll, int level, bool state)
{
	SetScene(scene);
	SetPos(x, y);
	m_useScroll = scroll;
	m_CharLevel = level;
	m_state = state;
	m_Speed = 0.0f;
}

void Player::ScrollInit(int x, int y)
{
	if (x != 0)		m_passScroll.x = x - 200;
	else			m_passScroll.x = 0;

	m_Scroll.x = m_passScroll.x;
}

void Player::SceneChange(int level)
{
	switch (level)
	{
	case 0:
		// ���� �����
		//SetSprite(14, 2, 14, 14, m_SpriteTime);
		//m_CharLevel = -1;
		//m_Gravity = 15.0f;
		//m_state = 1;

		SetCollTime(100);
		SetCollPauseTime(100);
		SetTempPauseTime(100);
		break;
	case 1: case 2:
		//m_CharLevel = 0;
		switch (m_DirLeftRight)
		{
		case 0:
			//SetSprite(14, 18, 14, 27, m_SpriteTime);
			break;
		case 1:
			//SetSprite(0, 18, 0, 13, m_SpriteTime);
			break;
		}
		SetCollTime(100);
		SetCollPauseTime(100);
		SetTempPauseTime(100);
		break;
	}
	//m_UseCollision		= false;
	m_secure = false;
	m_secure2 = false;
	m_tempPause = true;
	m_collPause = true;
	m_tempPauseTime = GetTickCount();
	m_collTime = GetTickCount();
	m_collPauseTime = GetTickCount();
	UpdateRect();	
}

void Player::SetTime(DWORD d)
{
	m_liveTime = d;
	m_liveTimeCount = GetTickCount();
}

void Player::LiveTime()
{
	if (GetTickCount() - m_liveTimeCount > 500) {
		m_liveTimeCount = GetTickCount();
		m_liveTime--;
		if (m_liveTime <= 0) {
			m_CharLevel = -1;
			/*SetSprite(14, 2, 14, 14, m_SpriteTime);
			m_secure = false;
			m_CharLevel = -1;
			m_Gravity = 15.0f;
			m_state = 1;

			SetCollTime(3000);
			SetCollPauseTime(2000);
			SetTempPauseTime(500);*/
		}
	}
	else {

	}
}

Player * Player::GetPlayer()
{
	static Player _Player;
	return &_Player;
}
