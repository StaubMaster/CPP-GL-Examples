#ifndef  VOXEL_GRAPHICS_DATA_HPP
# define VOXEL_GRAPHICS_DATA_HPP

# include "Graphics/Voxel.hpp"
# include "VoxelOrientation.hpp" // only for AxisRel
# include "Miscellaneous/Container/Binary.hpp"

struct VectorU3;

//truct VoxelOrientation;
struct VoxelGraphicsTemplate;
struct VoxelTemplate;
struct Voxel;

struct VoxelGraphicsData
{
	Container::Binary<VoxelGraphics::MainTriangle>	Data;

	void	Concatnate(VectorU3 u, const VoxelOrientation & orientation, unsigned int tex, const VoxelGraphicsData & other);
	void	Concatnate(VectorU3 u, const VoxelOrientation & orientation, unsigned int tex, const VoxelGraphicsTemplate & graphics_temp, AxisRel axis);
	void	Concatnate(VectorU3 u, const VoxelOrientation & orientation, const VoxelTemplate & temp, AxisRel axis);
	void	Concatnate(VectorU3 u, const Voxel & voxel, AxisRel axis);
};

#endif