#ifndef  TILE_FEATURE_OBJECT_COIN_HPP
# define TILE_FEATURE_OBJECT_COIN_HPP

# include "Tile/Feature/Object.hpp"

# include "EPath.hpp"

# include "NewPolyHedra/DataType/Basic3D/PalletObjectManager.hpp"

# include "ValueType/Vector/F2.hpp"
# include "ValueType/Box/F2.hpp"

/*
should collected coins be removed or made invisible and uninteractible
or should coins be independently simulated objects
*/
struct TileFeatureObjectCoin : public TileFeatureObject
{
	bool	IsCollected;
	EPath	Path;
	EPath	Side;
	BoxF2	Box;

	TileFeatureObjectCoin(EPath path, EPath side, BoxF2 box);

	PlayerChange	CheckPlayer(const Player & player) override;

	static NewPolyHedra::Basic3D::PalletObjectManager *		Object;
	static NewPolyHedra::Basic3D::PalletObjectManager *		ObjectBox;

	void	Display(const TileObject & tile, const Trans3D & trans) const override;
};

#endif
