#ifndef  VOXEL_GRAPHICS_MAIN_BUFFER_HPP
# define VOXEL_GRAPHICS_MAIN_BUFFER_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Attribute/VectorF3.hpp"

namespace VoxelGraphics
{
	struct MainBuffer : public ::Buffer::Array
	{
		::Attribute::VectorF3	Pos;
		::Attribute::VectorF3	Tex;
		~MainBuffer();
		MainBuffer(::VertexArray & vertex_array);
	};
};

#endif