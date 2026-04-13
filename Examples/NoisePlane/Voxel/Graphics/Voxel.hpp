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
		VoxelFace	Face[6];
	};
};

#endif