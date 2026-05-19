#ifndef  VOXEL_GRAPHICS_BUFFER_HPP
# define VOXEL_GRAPHICS_BUFFER_HPP

# include "Main/Buffer.hpp"
# include "Inst/Buffer.hpp"

# include "Graphics/Buffer/MainInst.hpp"
# include "Graphics/Buffer/Main.hpp"

namespace VoxelGraphics
{
	struct BufferF : public ::BufferArray::MainInst<MainBufferF, InstBuffer>
	{
		~BufferF();
		BufferF();
	};
	struct BufferU : public ::BufferArray::Main<MainBufferU>
	{
		~BufferU();
		BufferU();
	};
};

#endif