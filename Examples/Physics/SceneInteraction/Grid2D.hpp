#ifndef  GRID_2D_HPP
# define GRID_2D_HPP

# include "ValueType/Point2D.hpp"
# include "ValueType/Angle2D.hpp"

struct Grid2D
{
	float	Lin;
	float	Ang;

	~Grid2D();
	Grid2D();
	Grid2D(float lin, float ang);

	Point2D		Align(Point2D p) const;
	Angle2D		Align(Angle2D a) const;
};

#endif