#ifndef  VOXEL_GEOMETRY_DATA_U_HPP
# define VOXEL_GEOMETRY_DATA_U_HPP

# include "ValueType/Vector/U3.hpp"
# include "ValueType/Vector/U2.hpp"

struct BoxU2;

namespace VoxelGeometryDataU
{
struct Vertex
{
	VectorU3		Pos;
	VectorU2		Tex;
	unsigned int	Idx; // Texture Index
};
struct Face
{
	Vertex	Vertexes[4];

	void	Quad0(VectorU3 p00, VectorU3 p01, VectorU3 p10, VectorU3 p11, BoxU2 box, unsigned int tex);
	void	Quad1(VectorU3 p00, VectorU3 p01, VectorU3 p10, VectorU3 p11, BoxU2 box, unsigned int tex);
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