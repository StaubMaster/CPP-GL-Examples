#include "Tile/Feature/Pallet/DeathWall.hpp"
#include "Tile/Pallet.hpp"

#include "Player.hpp"
#include "EPath.hpp"
#include "PlayerChange.hpp"



TileFeaturePalletDeathWall::TileFeaturePalletDeathWall(EPath path, EPath side, BoxF1 dist, BoxF1 height)
	: TileFeaturePallet()
	, Path(path)
	, Side(side)
	, Dist(dist)
	, Height(height)
{ }



PlayerChange TileFeaturePalletDeathWall::CheckPlayer(const Player & player) const
{
	BoxF3 box = player.Box + VectorF3(0, player.Height, player.TileDistance);
	PlayerChange h;
	if (player.Path == Path &&
		player.Side == Side &&
		(box.Max.Z > Dist.Min && box.Min.Z < Dist.Max) &&
		(box.Max.Y > Height.Min && box.Min.Y < Height.Max)
	)
	{
		h.DeathWall = true;
	}
	return h;
}



NewPolyHedra::Basic3D::PalletObjectManager * TileFeaturePalletDeathWall::Object = nullptr;

void TileFeaturePalletDeathWall::Display(const TilePallet & pallet, const Trans3D & trans) const
{
	NewPolyHedra::Basic3D::ObjectData data;

	float side = 0.0f;
	if (Side == EPath::Left)	{ side = -15.0f; }
	if (Side == EPath::Right)	{ side = +15.0f; }

	data.Trans = pallet.Target(Path, Dist.Min);
	data.Trans.Position.X = side;
	data.Trans.Position.Y = Height.Min;
	data.Trans = trans.forward(data.Trans);
	Object -> InstancesFullPut(data);

	data.Trans = pallet.Target(Path, Dist.Max);
	data.Trans.Position.X = side;
	data.Trans.Position.Y = Height.Min;
	data.Trans = trans.forward(data.Trans);
	Object -> InstancesFullPut(data);

	data.Trans = pallet.Target(Path, Dist.Min);
	data.Trans.Position.X = side;
	data.Trans.Position.Y = Height.Max;
	data.Trans = trans.forward(data.Trans);
	Object -> InstancesFullPut(data);

	data.Trans = pallet.Target(Path, Dist.Max);
	data.Trans.Position.X = side;
	data.Trans.Position.Y = Height.Max;
	data.Trans = trans.forward(data.Trans);
	Object -> InstancesFullPut(data);
}
