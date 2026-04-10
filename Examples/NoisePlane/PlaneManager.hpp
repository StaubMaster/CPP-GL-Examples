#ifndef  PLANE_MANAGER_HPP
# define PLANE_MANAGER_HPP

# include "Perlin2D.hpp"
# include "Plane.hpp"
# include "PlaneGraphics.hpp"
# include "PlaneNeighbours.hpp"

# define PLANES_PER_SIDE 8
# define PLANES_PER_AREA PLANES_PER_SIDE * PLANES_PER_SIDE

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
	PlaneGraphics::Shader	Shader;

	Plane		Planes[PLANES_PER_AREA];

	~PlaneManager();
	PlaneManager();
	PlaneManager(const PlaneManager & other) = delete;
	PlaneManager & operator=(const PlaneManager & other) = delete;

	void	GenerateAround(const Perlin2D & noise, Point2D pos);

	void				PlanesToBuffers();
	void				UpdateNeighboursAround(Plane & plane);

	void	Update();

	bool	GraphicsExist;
	void	GraphicsCreate();
	void	GraphicsDelete();

	void	Draw();
};

#endif