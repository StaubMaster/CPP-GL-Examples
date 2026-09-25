#ifndef  TILE_FEATURE_PALLET_DEATH_WALL_HPP
# define TILE_FEATURE_PALLET_DEATH_WALL_HPP

# include "Tile/Feature/Pallet.hpp"

# include "EPath.hpp"

# include "NewPolyHedra/DataType/Basic3D/PalletObjectManager.hpp"

# include "ValueType/Box/F1.hpp"

struct TileFeaturePalletDeathWall : public TileFeaturePallet
{
	EPath	Path;
	EPath	Side;
	BoxF1	Dist;
	BoxF1	Height;

	TileFeaturePalletDeathWall(EPath path, EPath side, BoxF1 dist, BoxF1 height);

	PlayerChange	CheckPlayer(const Player & player) const override;

	static NewPolyHedra::Basic3D::PalletObjectManager *		Object;

	void	Display(const TilePallet & pallet, const Trans3D & trans) const override;
};

#endif