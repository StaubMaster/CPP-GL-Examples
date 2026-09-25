#ifndef  TILE_FEATURE_PALLET_HPP
# define TILE_FEATURE_PALLET_HPP

struct Trans3D;
struct Player;

struct PlayerChange;
struct TilePallet;
struct TileObject;

struct TileFeaturePallet
{
	virtual ~TileFeaturePallet() = default;

	virtual void	PutObjects(TileObject & object) const;

	virtual PlayerChange	CheckPlayer(const Player & player) const;

	virtual void	Display(const TilePallet & pallet, const Trans3D & trans) const;
};

#endif