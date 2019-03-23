#include "Shape_Stick.h"



void Shape_Stick::Init(){
	m_iType = SR_STICK;

	m_ArrShape[4][4] = { 0, };
	m_ArrShape[0][3] = 1;
	m_ArrShape[1][3] = 1;
	m_ArrShape[2][3] = 1;
	m_ArrShape[3][3] = 1;
}

void Shape_Stick::Update()
{
}

void Shape_Stick::Render(){
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (m_ArrShape[i][j] == 1) {
				g_pDB->WriteBuffer((i + 5) * 2, j-1, "бс");
			}
		}
	}
}

void Shape_Stick::Release()
{
}

Shape_Stick::Shape_Stick()
{
}


Shape_Stick::~Shape_Stick()
{
}
