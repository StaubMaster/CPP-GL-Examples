#ifndef  VOXEL_GRAPHICS_INST_BUFFER_HPP
# define VOXEL_GRAPHICS_INST_BUFFER_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Attribute/Layout.hpp"
# include "Graphics/Attribute/_Include.hpp"

namespace VoxelGraphics
{
	struct InstBuffer : public ::Buffer::Array
	{
		~InstBuffer();
		InstBuffer(::VertexArray & vertex_array);
	};
	struct InstLayout : public ::Attribute::Layout
	{
		::Attribute::VectorF3	Pos;
		~InstLayout();
		InstLayout();
	};
};


#endif