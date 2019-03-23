#pragma once
#include "Player.h"
#include "Monster.h"
#include <list>

class CharacterManager
{
public:
	CharacterManager();
	~CharacterManager();

	static Player*		GetPlayer();

	//static list<Monster>*		GetMonster();
	static Monster*		GetMonster();
};

