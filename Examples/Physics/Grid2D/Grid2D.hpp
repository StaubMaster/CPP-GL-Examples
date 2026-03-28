#ifndef  GRID_2D_HPP
# define GRID_2D_HPP

# include "ValueType/Point2D.hpp"
# include "ValueType/Angle2D.hpp"

/*
change Grid based on Zoom
use Shift when Mobving to not align to Grid
use Numbers to change "Tool"
*/

struct Grid2D
{
	unsigned int LinSections;
	unsigned int AngSections;

	float	Lin;
	float	Ang;

	~Grid2D();
	Grid2D();
	Grid2D(unsigned lin, unsigned ang);

	Point2D		Align(Point2D p) const;
	Angle2D		Align(Angle2D a) const;
};

#endif