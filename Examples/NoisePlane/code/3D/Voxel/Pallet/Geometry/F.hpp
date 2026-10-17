#ifndef  VOXEL_GEOMETRY_DATA_F_HPP
# define VOXEL_GEOMETRY_DATA_F_HPP

# include "ValueType/Vector/F3.hpp"
# include "ValueType/Vector/F2.hpp"
struct BoxF2;

# include "Generics/Container/Binary.hpp"
# include "Generics/Container/Array.hpp"
# include "Generics/Container/BlockLinkedList.hpp"

namespace VoxelGeometryDataF
{
struct Vertex
{
	VectorF3	Pos;
	VectorF2	Tex;

	~Vertex() = default;
	Vertex() = default;
	Vertex(const Vertex & other) = default;
	Vertex & operator=(const Vertex & other) = default;

	Vertex(VectorF3 pos, VectorF2 tex);
};
struct Face
{
	Vertex			Vertexes[3];
	VectorF3		Normal;
	unsigned int	Tex;

	~Face() = default;
	Face() = default;
	Face(const Face & other) = default;
	Face & operator=(const Face & other) = default;

	void	CalcNormal();
};
struct Axis
{
	Container::Binary<Face>		Data;

	void	Tri0(VectorF3 p0, VectorF3 p1, VectorF3 p2, VectorF2 t0, VectorF2 t1, VectorF2 t2, unsigned int tex);
	void	Tri1(VectorF3 p0, VectorF3 p1, VectorF3 p2, VectorF2 t0, VectorF2 t1, VectorF2 t2, unsigned int tex);

	void	Quad1(VectorF3 p00, VectorF3 p01, VectorF3 p10, VectorF3 p11, BoxF2 box, unsigned int tex);
	void	Quad0(VectorF3 p00, VectorF3 p01, VectorF3 p10, VectorF3 p11, BoxF2 box, unsigned int tex);

	void	Done();
};
struct Full
{
	Axis	Here;
	Axis	PrevX;
	Axis	PrevY;
	Axis	PrevZ;
	Axis	NextX;
	Axis	NextY;
	Axis	NextZ;

	void	Done();

//	const VoxelAxisGraphicsDataF &	AxisData(Axis3D::Rel axis) const;
};
};

#endif