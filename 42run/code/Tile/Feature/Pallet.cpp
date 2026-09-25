#include "Tile/Feature/Pallet.hpp"

#include "PlayerChange.hpp"



void TileFeaturePallet::PutObjects(TileObject & object) const
{
	(void)object;
}

PlayerChange TileFeaturePallet::CheckPlayer(const Player & player) const
{
	(void)player;
	return PlayerChange();
}

void TileFeaturePallet::Display(const TilePallet & pallet, const Trans3D & trans) const
{
	(void)pallet;
	(void)trans;
}
