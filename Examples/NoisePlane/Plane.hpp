#ifndef  PLANE_HPP
# define PLANE_HPP

# define PLANE_SCALE 0.0625
# define PLANE_CELL_PER_SIDE 16
# define PLANE_CELL_PER_AREA PLANE_CELL_PER_SIDE * PLANE_CELL_PER_SIDE

# include "ValueType/Point2D.hpp"
# include "ValueType/Point3D.hpp"
# include "ValueType/Undex2D.hpp"

struct Perlin2D;

struct Plane
{
	float		Heights[PLANE_CELL_PER_AREA];
	Point2D		Pos; // Plane Scale

	~Plane();
	Plane();
	Plane(const Plane & other) = delete;
	Plane & operator=(const Plane & other) = delete;

	Point2D Pos2At(Undex2D u) const;
	Point3D Pos3At(Undex2D u) const;

	void Generate(const Perlin2D & noise);
};

#endif
