#ifndef  VOXEL_GRAPHICS_BUFFER_HPP
# define VOXEL_GRAPHICS_BUFFER_HPP

# include "Main/Buffer.hpp"
# include "Inst/Buffer.hpp"

# include "Graphics/Buffer/MainInst.hpp"

namespace VoxelGraphics
{
	struct Buffer : public ::BufferArray::MainInst<MainBuffer, InstBuffer>
	{
		~Buffer();
		Buffer();
	};
};

#endif