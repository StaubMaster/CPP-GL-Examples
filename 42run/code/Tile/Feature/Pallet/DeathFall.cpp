#include "Tile/Feature/Pallet/DeathFall.hpp"
#include "Tile/Pallet.hpp"

#include "Player.hpp"
#include "EPath.hpp"
#include "PlayerChange.hpp"



TileFeaturePalletDeathFall::TileFeaturePalletDeathFall(EPath path, EPath side, BoxF1 dist)
	: TileFeaturePallet()
	, Path(path)
	, Side(side)
	, Dist(dist)
{ }



PlayerChange TileFeaturePalletDeathFall::CheckPlayer(const Player & player) const
{
	BoxF3 box = player.Box + VectorF3(0, player.Height, player.TileDistance);
	PlayerChange h;
	if (player.Path == Path && player.Side == Side &&
		player.Height <= 0.0f &&
		(box.Min.Z > Dist.Min) &&
		(box.Max.Z < Dist.Max)
	)
	{
		h.NotAboveGround = true;
	}
	return h;
}



NewPolyHedra::Basic3D::PalletObjectManager * TileFeaturePalletDeathFall::Object = nullptr;

void TileFeaturePalletDeathFall::Display(const TilePallet & pallet, const Trans3D & trans) const
{
	NewPolyHedra::Basic3D::ObjectData data;

	float side = 0.0f;
	if (Side == EPath::Left)	{ side = -15.0f; }
	if (Side == EPath::Right)	{ side = +15.0f; }

	data.Trans = pallet.Target(Path, Dist.Min);
	data.Trans.Position.X = side;
	data.Trans = trans.forward(data.Trans);
	Object -> InstancesFullPut(data);

	data.Trans = pallet.Target(Path, Dist.Max);
	data.Trans.Position.X = side;
	data.Trans = trans.forward(data.Trans);
	Object -> InstancesFullPut(data);
}
