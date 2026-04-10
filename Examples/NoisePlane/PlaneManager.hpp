#ifndef  PLANE_MANAGER_HPP
# define PLANE_MANAGER_HPP

# include "Perlin2D.hpp"
# include "Plane.hpp"
# include "PlaneGraphics.hpp"
# include "PlaneNeighbours.hpp"

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

struct PlaneManager
{
	PlaneGraphics::Shader		Shader;
	Container::Binary<Plane*>	Planes;

	~PlaneManager();
	PlaneManager();
	PlaneManager(const PlaneManager & other) = delete;
	PlaneManager & operator=(const PlaneManager & other) = delete;

	unsigned int	FindPlaneUndex(Plane * plane) const;
	unsigned int	FindPlaneUndex(Undex2D udx) const;
	Plane *			FindPlaneOrNull(Undex2D udx) const;

	void	GenerateAround(const Perlin2D & noise, Point2D pos);

	void	UpdateNeighboursAround(Plane & plane);

	void	Update();

	bool	GraphicsExist;
	void	GraphicsCreate();
	void	GraphicsDelete();

	void	Draw();
};

#endif