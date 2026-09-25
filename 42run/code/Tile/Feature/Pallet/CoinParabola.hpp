#ifndef  TILE_FEATURE_PALLET_COIN_PARABOLA_HPP
# define TILE_FEATURE_PALLET_COIN_PARABOLA_HPP

# include "Tile/Feature/Pallet.hpp"

# include "Generics/Container/Array.hpp"
# include "ValueType/Vector/F2.hpp"

# include "EPath.hpp"

struct Player;

struct TileFeaturePalletCoinParabola : public TileFeaturePallet
{
	EPath	Path;
	EPath	Side;
	Container::Array<VectorF2>	Coins;

	TileFeaturePalletCoinParabola(const Player & player, EPath path, EPath side, float center);

	void	PutObjects(TileObject & object) const override;
};

#endif