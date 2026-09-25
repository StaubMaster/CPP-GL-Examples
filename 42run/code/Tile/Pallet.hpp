#ifndef  TILE_PALLET_HPP
# define TILE_PALLET_HPP

# include "ValueType/Trans/3D.hpp"

# include "NewPolyHedra/DataType/Basic3D/PalletObjectManager.hpp"

struct Player;

# include "EPath.hpp"

struct PlayerChange;

# include "NodePath.hpp"

struct TileFeaturePallet;

# include "Generics/Container/Binary.hpp"

struct TileObject;

struct TilePalletDisplayOptions;

struct TilePallet
{
	~TilePallet();

	void		Init();

	NodePath	PathTo;
	float		LengthTo[3];
	NodePath	Path[3];

	bool		HasPath(EPath path) const;
	float		PathLimit(EPath path) const;
	Trans3D		Target(EPath path, float t) const;



	bool		CanChoosePath(const Player & player) const;
	EPath		ChoosePath(EPath path_choice, const Player & player) const;



	Container::Binary<TileFeaturePallet*>	Features;
	PlayerChange	CheckPlayer(const Player & player) const;



	NewPolyHedra::Basic3D::PalletObjectManager *	Object = nullptr;

	static NewPolyHedra::Basic3D::PalletObjectManager *		ObjectManagerEntry;
	static NewPolyHedra::Basic3D::PalletObjectManager *		ObjectManagerExit;

	Trans3D		TransEntry;
	Trans3D		TransExit[3];
	void	Display(const Trans3D & trans, const TilePalletDisplayOptions & display_options) const;



	TileObject *	ToObject() const;
};

#endif