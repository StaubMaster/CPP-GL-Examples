#include "Tile/Feature/Object/Coin.hpp"
#include "Tile/Object.hpp"
#include "Tile/Pallet.hpp"
#include "Player.hpp"
#include "PlayerChange.hpp"



TileFeatureObjectCoin::TileFeatureObjectCoin(EPath path, EPath side, BoxF2 box)
	: TileFeatureObject()
	, IsCollected(false)
	, Path(path)
	, Side(side)
	, Box(box)
{ }



PlayerChange TileFeatureObjectCoin::CheckPlayer(const Player & player)
{
	PlayerChange h;
	if (IsCollected) { return h; }
	if (Path != player.Path) { return h; }
	if (Side != player.Side) { return h; }

	BoxF3 box = player.Box + VectorF3(0, player.Height, player.TileDistance);

	if ((box.Max.Z > Box.Min.X) &&
		(box.Min.Z < Box.Max.X) &&
		(box.Max.Y > Box.Min.Y) &&
		(box.Min.Y < Box.Max.Y)
	)
	{
		IsCollected = true;
		h.Coins += 1;
	}

	return h;
}



NewPolyHedra::Basic3D::PalletObjectManager * TileFeatureObjectCoin::Object = nullptr;
NewPolyHedra::Basic3D::PalletObjectManager * TileFeatureObjectCoin::ObjectBox = nullptr;

void TileFeatureObjectCoin::Display(const TileObject & tile, const Trans3D & trans) const
{
	if (IsCollected) { return; }

	VectorF2 center = Box.Center();

	NewPolyHedra::Basic3D::ObjectData data;

	data.Trans = trans.forward(tile.Pallet.Target(EPath::Middle, center.X));
	data.Trans.Position.Y += center.Y;
	Object -> InstancesFullPut(data);

	ObjectBox -> InstancesWirePut(data);
}
