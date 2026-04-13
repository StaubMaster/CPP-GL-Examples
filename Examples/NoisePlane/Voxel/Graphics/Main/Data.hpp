#ifndef  VOXEL_GRAPHICS_MAIN_DATA_HPP
# define VOXEL_GRAPHICS_MAIN_DATA_HPP

# include "ValueType/Point3D.hpp"
# include "ValueType/ColorF4.hpp"

namespace VoxelGraphics
{
	struct MainData
	{
		Point3D		Pos;
		ColorF4		Col;
	};
};

#endif