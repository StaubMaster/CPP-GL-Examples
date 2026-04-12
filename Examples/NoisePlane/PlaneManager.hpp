#ifndef  PLANE_MANAGER_HPP
# define PLANE_MANAGER_HPP

# include "Perlin2D.hpp"
# include "Plane.hpp"
# include "PlaneGraphics.hpp"
# include "PlaneNeighbours.hpp"

# include "ValueType/VectorI2.hpp"

# include "Miscellaneous/Container/Binary.hpp"

/*
Plane Undex2D should be Index2D
then make them generate around View (Point)
*/

/* Values to Tiles
right now the Planes are made of Values
which are connected into Tiles, with the Values being the Corners
change it so the Value is the Center of a Tile ?
this whould require knowing all Neighbours, not just positive

store Neighbours int Planes ?
*/

/*
	when "making" Planes
	start with the closest first, then go outward
	when too many are rendered, remove all and start over.
*/

struct PlaneManager
{
	PlaneGraphics::Shader		Shader;
	Container::Binary<Plane*>	Planes;

	~PlaneManager();
	PlaneManager();
	PlaneManager(const PlaneManager & other) = delete;
	PlaneManager & operator=(const PlaneManager & other) = delete;

	unsigned int	FindPlaneUndex(Plane * plane) const;
	unsigned int	FindPlaneUndex(VectorI2 idx) const;
	Plane *			FindPlaneOrNull(VectorI2 idx) const;

	void	Clear();
	void	UpdateAround(const Perlin2D & noise, Point2D pos);

	bool	ShouldGenerate;
	void	Generate(const Perlin2D & noise, VectorI2 idx);
	void	NeighbourInsert(Plane & plane);

	bool	GraphicsExist;
	void	GraphicsCreate();
	void	GraphicsDelete();

	void	Draw();
};

#endif