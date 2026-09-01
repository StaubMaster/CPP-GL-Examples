#ifndef  VOXEL_GEOMETRY_DATA_F_HPP
# define VOXEL_GEOMETRY_DATA_F_HPP

# include "Graphics/F/Data.hpp"

# include "Generics/Container/Binary.hpp"
# include "Generics/Container/Array.hpp"
# include "Generics/Container/BlockLinkedList.hpp"

namespace VoxelGeometryDataF
{
struct Axis
{
	Container::Binary<VoxelGraphicsDataF::Face>	Data;

	// Clear()
	// Count()
	// operator[]
	// Insert()

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

//	const VoxelAxisGraphicsDataF &	AxisData(AxisRel axis) const;
};
};

#endif