#ifndef  TILE_FEATURE_OBJECT_HPP
# define TILE_FEATURE_OBJECT_HPP

struct Player;
struct PlayerChange;
struct TileObject;
struct Trans3D;

struct TileFeatureObject
{
	virtual ~TileFeatureObject() = default;

	virtual PlayerChange	CheckPlayer(const Player & player) = 0;

	virtual void	Display(const TileObject & tile, const Trans3D & trans) const = 0;
};

#endif
