#ifndef  VOXEL_GEOMETRY_DATA_U_HPP
# define VOXEL_GEOMETRY_DATA_U_HPP

# include "ValueType/Vector/U3.hpp"

namespace VoxelGeometryDataU
{
struct Vertex
{
	VectorU3	Pos;
	VectorU3	Tex;
};
struct Face
{
	Vertex	Data[4];
};
struct Cube
{
	Face	PrevX;
	Face	PrevY;
	Face	PrevZ;
	Face	NextX;
	Face	NextY;
	Face	NextZ;
};
};

#endif