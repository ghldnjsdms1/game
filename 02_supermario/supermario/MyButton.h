#pragma once
#include "Button.h"

class MyButton : public Button
{
public:
	MyButton();
	virtual ~MyButton();

// Variable__
private:

public:


// Method__
private:

public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC memDC, HDC backMemDC);

};

