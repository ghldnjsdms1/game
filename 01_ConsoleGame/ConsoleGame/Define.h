#pragma once

#include <Windows.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <list> // STL �ڷᱸ��
#include <map>  // STL �ڷᱸ��

using namespace std;

#define CONSOLE_MAX_WIDTH 150	// �ܼ� ����ũ��
#define CONSOLE_MAX_HEIGHT 100	// �ܼ� ����ũ��

// ���� �޴�
#define MENU_GAME_START				0x0000
//#define MENU_GAME_EXIT				0x0001
#define MENU_GAME_RETURN			0x0002
#define MENU_SEL_STAGE				0x0003
#define MENU_SEL_STAGE2				0x0004
#define MENU_SEL_STAGE3_EarthWarm	0x0005
#define MENU_GAME_EXIT				0x0006

// ������ ���ǵ�
#define WARM_SPEED			240

enum SHAPE_TYPE { SR_RECT, SR_STICK, SR_END };

// �ܼ� ����ǥ
#define BLACK			0
#define BLUE			1
#define GREEN			2
#define CYAN			3
#define RED				4
#define MAGENTA			5
#define BROWN			6
#define LIGHTGRAY		7
#define DARKGRAY		8
#define LIGHTBLUE		9
#define LIGHTGREEN		10
#define LIGHTCYAN		11
#define LIGHTRED		12
#define LIGHTMAGENTA	13
#define YELLOW			14
#define WHITE			15



