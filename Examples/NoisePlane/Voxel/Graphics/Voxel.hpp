#ifndef  CHUNK_GRAPHICS_HPP
# define CHUNK_GRAPHICS_HPP

# include "Main/Data.hpp"

namespace VoxelGraphics
{
	struct VoxelFace
	{
		MainData	Corn[4];
	};
	struct VoxelCube
	{
		VoxelFace	NextX;
		VoxelFace	NextY;
		VoxelFace	NextZ;
		VoxelFace	PrevX;
		VoxelFace	PrevY;
		VoxelFace	PrevZ;
	};
};

#endif