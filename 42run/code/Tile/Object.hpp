#ifndef  TILE_OBJECT_HPP
# define TILE_OBJECT_HPP

# include "NewPolyHedra/DataType/Basic3D/PalletObjectData.hpp"

struct TilePallet;
struct TileFeatureObject;

# include "Generics/Container/Binary.hpp"

struct Player;
struct PlayerChange;

struct TilePalletDisplayOptions;

# include "EPath.hpp"

struct TileObject
{
	const TilePallet &	Pallet;

	TileObject *	Entry = nullptr;
	TileObject *	Exit[3] = { nullptr, nullptr, nullptr };

	EPath	EntryExit = EPath::Middle;

	void	TrimEntry();
	void	TrimExit(EPath path);

	void	ConnectEntry(TileObject * tile, EPath path);
	void	ConnectExit(TileObject * tile, EPath path);

	~TileObject();
	TileObject() = delete;
	TileObject(const TilePallet & pallet);

	Container::Binary<TileFeatureObject*>	Features;
	PlayerChange	CheckPlayer(const Player & player) const;

	void	DisplayThis(Trans3D trans, const TilePalletDisplayOptions & display_options) const;
	void	Display(Trans3D trans, const TilePalletDisplayOptions & display_options) const;
	void	DisplayEntry(Trans3D trans, EPath path, const TilePalletDisplayOptions & display_options) const;
	void	DisplayExit(Trans3D trans, const TilePalletDisplayOptions & display_options) const;
};

#endif