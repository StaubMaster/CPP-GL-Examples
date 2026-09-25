#include "Tile/Feature/Pallet/CoinParabola.hpp"
#include "Tile/Feature/Object/Coin.hpp"
#include "Tile/Object.hpp"

#include "PlayerChange.hpp"
#include "Player.hpp"



TileFeaturePalletCoinParabola::TileFeaturePalletCoinParabola(const Player & player, EPath path, EPath side, float center)
	: TileFeaturePallet()
	, Path(path)
	, Side(side)
{
	(void)player;

	Coins.NewLength(9);
	Coins[0] = VectorF2(center - 80,  0.0f + 8.0f);
	Coins[1] = VectorF2(center - 60,  0.0f + 8.0f);
	Coins[2] = VectorF2(center - 40,  0.0f + 8.0f);
	Coins[3] = VectorF2(center - 20,  0.5f + 8.0f);
	Coins[4] = VectorF2(center     , 52.5f + 8.0f);
	Coins[5] = VectorF2(center + 20,  0.0f + 8.0f);
	Coins[6] = VectorF2(center + 40,  0.0f + 8.0f);
	Coins[7] = VectorF2(center + 60,  0.0f + 8.0f);
	Coins[8] = VectorF2(center + 80,  0.0f + 8.0f);
}



void TileFeaturePalletCoinParabola::PutObjects(TileObject & object) const
{
	for (unsigned int i = 0; i < Coins.Length(); i++)
	{
		BoxF2 box(VectorF2(-4), VectorF2(+4));

		box.Min.X += Coins[i].X;
		box.Max.X += Coins[i].X;

		box.Min.Y += Coins[i].Y;
		box.Max.Y += Coins[i].Y;

		object.Features.Insert(new TileFeatureObjectCoin(Path, Side, box));
	}
}
