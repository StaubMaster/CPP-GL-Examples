#ifndef  VOXEL_HPP
# define VOXEL_HPP

# include "VoxelOrientation.hpp"

struct VoxelPallet;

struct Voxel
{
/* sizeof
	this whole thing is 16 Bytes
	Pallet is 8 Bytes
	Orientation is 1 Bytes
	9 Bytes gets rounded up to 16 Bytes

	Pallet is a 64 Bit Pointer
	use a 16 Bit Index
	65536 is enough ?

	structs align to the Largest member
	16 Bit Index would make the Voxel 4 Bytes
*/

//	const VoxelPallet *		Pallet;
	unsigned short		Pallet;
	VoxelOrientation	Orientation;

	bool	Visible(AxisRel axis) const;

	~Voxel();
	Voxel();

	Voxel(const Voxel & other);
	Voxel & operator=(const Voxel & other);
};

#endif
