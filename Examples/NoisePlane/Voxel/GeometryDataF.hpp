#ifndef  VOXEL_GEOMETRY_DATA_F_HPP
# define VOXEL_GEOMETRY_DATA_F_HPP

# include "Graphics/DataF.hpp"

# include "Generics/Container/Binary.hpp"
# include "Generics/Container/Array.hpp"
# include "Generics/Container/BlockLinkedList.hpp"

namespace VoxelGeometryDataF
{
struct Face
{
	Container::Binary<VoxelGraphicsDataF::Face>	Data;

	// Clear()
	// Count()
	// operator[]
	// Insert()

	void	Done();
};
struct Full
{
	Face	Here;
	Face	PrevX;
	Face	PrevY;
	Face	PrevZ;
	Face	NextX;
	Face	NextY;
	Face	NextZ;

	void	Done();

//	const VoxelAxisGraphicsDataF &	AxisData(AxisRel axis) const;
};
};

#endif