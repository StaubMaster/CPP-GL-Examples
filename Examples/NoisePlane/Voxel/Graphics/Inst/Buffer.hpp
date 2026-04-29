#ifndef  VOXEL_GRAPHICS_INST_BUFFER_HPP
# define VOXEL_GRAPHICS_INST_BUFFER_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Attribute/VectorF3.hpp"

namespace VoxelGraphics
{
	struct InstBuffer : public ::Buffer::Array
	{
		::Attribute::VectorF3	Pos;
		~InstBuffer();
		InstBuffer(::VertexArray & vertex_array);
	};
};


#endif