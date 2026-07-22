#ifndef  VOXEL_GRAPHICS_BUFFER_HPP
# define VOXEL_GRAPHICS_BUFFER_HPP

# include "Graphics/VertexArray/Multi.hpp"

namespace VoxelGraphics
{
	typedef VertexArray::Multi BufferU;
	typedef VertexArray::Multi::Entry BufferEntryU;

	typedef VertexArray::Multi BufferF;
	typedef VertexArray::Multi::Entry BufferEntryF;
//	typedef VertexArray::MainInst BufferF;
};

#endif