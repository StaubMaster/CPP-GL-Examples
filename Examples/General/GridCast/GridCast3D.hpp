#ifndef  GRID_CAST_3D_HPP
# define GRID_CAST_3D_HPP

# include "ValueType/Vector/F3.hpp"
# include "ValueType/Vector/I3.hpp"

# include "General/Axis/Enums.hpp"

# include "ValueType/Ray3D.hpp"

namespace GridCast3D
{

struct Data
{
	float		scale;
	float		limit;
	VectorF3	pos;
	VectorF3	dir;

	float		sum;

	VectorF3	side_len;
	VectorF3	side_sum;

	VectorI3	grid_dir;
	VectorI3	grid_idx;

	AxisRel		cardinal_side_X;
	AxisRel		cardinal_side_Y;
	AxisRel		cardinal_side_Z;
	AxisRel		cardinal_dir;

	VectorI3	Index() const;
	float		Distance() const;
	float		Limit() const;
	Ray3D		Ray() const;

	Data(Ray3D ray, float limit, float scale);
	bool	Iterate();
};

struct Hit
{
	VectorF3	pos;
	VectorF3	rel;
	VectorI3	idx;
	float		dist;
	AxisRel		cardinal;

	Hit();
	Hit(Data data);
};



};

#endif