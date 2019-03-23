#include "CharacterManager.h"



CharacterManager::CharacterManager()
{
}


CharacterManager::~CharacterManager()
{
}

Player * CharacterManager::GetPlayer()
{
	static Player _Player;
	return &_Player;
}

Monster * CharacterManager::GetMonster()
{
	static Monster _Monster;
	return &_Monster;
}

//list<Monster>* CharacterManager::GetMonster()
//{
//	static list<Monster> _Monster;
//	return &_Monster;
//}

//Monster * CharacterManager::GetMonster()
//{
//	static list<Monster> _Monster;
//	return _Monster;
//}
