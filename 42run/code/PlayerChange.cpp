#include "PlayerChange.hpp"



void PlayerChange::MakeDefault()
{
	DeathWall = false;
	NotAboveGround = false;
	Coins = 0;
}
void PlayerChange::Consider(const PlayerChange & other)
{
	DeathWall |= other.DeathWall;
	NotAboveGround |= other.NotAboveGround;
	Coins += other.Coins;
}
