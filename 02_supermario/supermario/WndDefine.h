#pragma once
#include <windows.h>
#include <string>
#include <crtdbg.h> // �޸� �� üũ��

using namespace std;
#pragma comment (lib, "Msimg32.lib")

// ���� �ܼ�â�� ����� ������ �����մϴ�.
#define USECONSOLE true

#if USECONSOLE == true
#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") // �ܼ�â�� ���ϴ�.
#endif


inline void Log(std::string log) {
#if USECONSOLE == true
	std::cout << log << std::endl;
#endif
}

template<typename T>
inline void Log(std::string log, T value) {
#if USECONSOLE == true
	std::cout << log << value << std::endl;
#endif
}

template<typename T>
inline void Log(std::string log, T value1, T value2) {
#if USECONSOLE == true
	std::cout << log << value1 << ", " << value2 << std::endl;
#endif
}



#define SCREENWIDTH				GetSystemMetrics(SM_CXSCREEN)		// ���� ȭ�� ���� ����
#define SCREENHEIGTH			GetSystemMetrics(SM_CYSCREEN)		// ���� ȭ�� ���� ����
#define GetMiddlePosX(width)	((SCREENWIDTH - width) / 2)			// â�� ȭ�� ��� ������ǥ
#define GetMiddlePosY(height)	((SCREENHEIGTH - height) / 2)		// â�� ȭ�� ��� ������ǥ


// �ʿ��� ������� �����մϴ�.
const	LPCWSTR g_WinClassName = L"WinAPI";			// â Ŭ���� �̸�
const	LPCWSTR g_WinTitleName = L"�����ӿ�ũ";		// Ÿ��Ʋ �� �̸�
const	int		MAIN_WND_WIDTH = 655;				// ������ â ���� ����
const	int		MAIN_WND_HEIGHT = 570;				// ������ â ���� ����

const	int		MAP_INDEX_WIDTH = 15;
const	int		MAP_INDEX_HEIGHT = 15;
const	int		MAP_TILE_SIZE = 32;

enum COLLISION_DIRECTION { COL_TOP, COL_BOTTOM, COL_LEFT, COL_RIGHT, COL_NONE };
enum CURRENT_SCENE { SCENE_PLAY, SCENE_PLAYBONUS, SCENE_SECOND, SCENE_MAKE, SCENE_MAINMENU, SCENE_GAMEOVER };

#define KEY_DOWN 0x01
#define KEY_PRESSED 0x02
#define KEY_RELEASE 0x03

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A