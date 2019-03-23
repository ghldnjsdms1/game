#pragma once
#include "Object.h"
#include "DoubleBuffer.h"

class Shape0 : public Object {
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

private:
	// ¤Ñ ¸ð¾ç
	int	m_Shape[4][4][4] = {
		{
			{ 1,1,1,1 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 }
		},
		{ 
			{ 1,0,0,0 },
			{ 1,0,0,0 },
			{ 1,0,0,0 },
			{ 1,0,0,0 } 
		},
		{ 
			{ 1,1,1,1 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 } 
		},
		{ 
			{ 1,0,0,0 },
			{ 1,0,0,0 },
			{ 1,0,0,0 },
			{ 1,0,0,0 } 
		}
	};

public:
	Shape0();
	~Shape0();
};

