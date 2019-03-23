#include "Food.h"



void Food::Init(){
	// (4,3)~(58, 16)
	srand((unsigned)time(NULL));
	m_posX = (rand() % 27) * 2 + 4;
	m_posY = rand() % 13 + 3;
}

void Food::Update(){
	/*srand((unsigned)time(NULL));
	m_posX = (rand() % 27) * 2 + 4;
	m_posY = rand() % 13 + 3;*/
}

void Food::Render(){
	g_pDB->WriteBuffer(m_posX, m_posY, "¡Ú");
}

void Food::Release()
{
}

void Food::Init(int x, int y){
	/*srand((unsigned)time(NULL));
	m_posX = (rand() % 27) * 2 + 4;
	m_posY = rand() % 13 + 3;*/
}

Food::Food()
{
}


Food::~Food()
{
}
