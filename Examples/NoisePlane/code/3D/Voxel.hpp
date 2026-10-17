#ifndef  VOXEL_HPP
# define VOXEL_HPP

# include "Axis/3D/Orientation.hpp"

struct VoxelPallet;

struct Voxel
{
	public:
	Axis3D::Orientation		Orientation;

	private:
	unsigned short	Pallet = 0xFFFF;
	public:
	bool					IsEmpty() const;
	void					MakeEmpty();
	const VoxelPallet &		ToPallet() const;
	void					MakePallet(const VoxelPallet & pallet);

	bool	IsAxisVisible(Axis3D::Rel axis) const;



	~Voxel() = default;
	Voxel() = default;
	Voxel(const Voxel & other) = default;
	Voxel & operator=(const Voxel & other) = default;
};

#endif
