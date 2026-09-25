#ifndef  TILE_FEATURE_PALLET_DEATH_FALL_HPP
# define TILE_FEATURE_PALLET_DEATH_FALL_HPP

# include "Tile/Feature/Pallet.hpp"

# include "EPath.hpp"

# include "NewPolyHedra/DataType/Basic3D/PalletObjectManager.hpp"

# include "ValueType/Box/F1.hpp"

struct TileFeaturePalletDeathFall : public TileFeaturePallet
{
	EPath	Path;
	EPath	Side;
	BoxF1	Dist;

	TileFeaturePalletDeathFall(EPath path, EPath side, BoxF1 dist);

	PlayerChange	CheckPlayer(const Player & player) const override;

	static NewPolyHedra::Basic3D::PalletObjectManager *		Object;

	void	Display(const TilePallet & pallet, const Trans3D & trans) const override;
};

#endif