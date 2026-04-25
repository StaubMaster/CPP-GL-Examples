#include "GridCast3D.hpp"

#include <math.h>



VectorI3	GridCast3D::Data::Index() const { return grid_idx; }
float		GridCast3D::Data::Distance() const { return sum * scale; }
float		GridCast3D::Data::Limit() const { return (limit - sum) * scale; }
Ray3D		GridCast3D::Data::Ray() const { return Ray3D( (pos + (dir * sum)) * scale, dir * scale); }



GridCast3D::Data::Data(Ray3D ray3D, float limit, float scale)
	: scale(scale)
	, limit(limit / scale)
	, pos(ray3D.Pos / scale)
	, dir(ray3D.Dir / scale)
	, sum(0.0f)
{
	grid_idx = pos.roundF();

	side_len = (dir.length() / dir).abs();

	side_sum = ((VectorF3)grid_idx) - pos;

	if (dir.X > 0)	{ grid_dir.X = +1; side_sum.X = 1 + side_sum.X; cardinal_side_X = AxisRel::PrevX; }
	else			{ grid_dir.X = -1; side_sum.X = 0 - side_sum.X; cardinal_side_X = AxisRel::NextX; }

	if (dir.Y > 0)	{ grid_dir.Y = +1; side_sum.Y = 1 + side_sum.Y; cardinal_side_Y = AxisRel::PrevY; }
	else			{ grid_dir.Y = -1; side_sum.Y = 0 - side_sum.Y; cardinal_side_Y = AxisRel::NextY; }

	if (dir.Z > 0)	{ grid_dir.Z = +1; side_sum.Z = 1 + side_sum.Z; cardinal_side_Z = AxisRel::PrevZ; }
	else			{ grid_dir.Z = -1; side_sum.Z = 0 - side_sum.Z; cardinal_side_Z = AxisRel::NextZ; }

	side_sum *= side_len;
}
bool GridCast3D::Data::Iterate()
{
	if ((side_sum.X < side_sum.Y) && (side_sum.X < side_sum.Z))
	{
		sum = side_sum.X;
		side_sum.X += side_len.X;
		grid_idx.X += grid_dir.X;
		cardinal_dir = cardinal_side_X;
	}
	else if ((side_sum.Y < side_sum.Z) && (side_sum.Y < side_sum.X))
	{
		sum = side_sum.Y;
		side_sum.Y += side_len.Y;
		grid_idx.Y += grid_dir.Y;
		cardinal_dir = cardinal_side_Y;
	}
	else
	{
		sum = side_sum.Z;
		side_sum.Z += side_len.Z;
		grid_idx.Z += grid_dir.Z;
		cardinal_dir = cardinal_side_Z;
	}

	if (sum >= limit) { return false; }
	return true;
}



GridCast3D::Hit::Hit()
{
	cardinal = AxisRel::None;
}
GridCast3D::Hit::Hit(Data data)
{
	dist = data.sum;
	idx = data.grid_idx;
	pos = data.pos + (data.dir * dist);
	rel = pos - idx;
	cardinal = data.cardinal_dir;
}
