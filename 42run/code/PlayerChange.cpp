#include "PlayerChange.hpp"



void PlayerChange::MakeDefault()
{
	IsDead = false;
	NotAboveGround = false;
	Coins = 0;
}
void PlayerChange::Consider(const PlayerChange & other)
{
	IsDead |= other.IsDead;
	NotAboveGround |= other.NotAboveGround;
	Coins += other.Coins;
}
