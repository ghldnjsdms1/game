#include "MyButton.h"



MyButton::MyButton()
{
	this->Init();
}


MyButton::~MyButton()
{
}

void MyButton::Init()
{
	LoadImg(L"Button.bmp", 0, 0);

	m_PosX = 150;
	m_PosY = 150;

	m_Width = 300;
	m_Height = 100;

	UpdateRect();

	m_ImgWidth = 300;
	m_ImgHeight = 100;

	// Over 속성을 사용하도록 설정합니다.
	m_UseOver = true;

	// 투명색을 사용합니다.
	m_UseTransparent = true;

	// 투명색을 지정합니다.
	TransparentColor = RGB(252, 0, 255);
}

void MyButton::Update()
{
	BaseUpdate();
}

void MyButton::Render(HDC memDC, HDC backMemDC)
{
	BaseRender(memDC, backMemDC);
}
