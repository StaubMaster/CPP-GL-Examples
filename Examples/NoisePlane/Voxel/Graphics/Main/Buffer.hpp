#ifndef  VOXEL_GRAPHICS_MAIN_BUFFER_HPP
# define VOXEL_GRAPHICS_MAIN_BUFFER_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Attribute/_Include.hpp"

namespace VoxelGraphics
{
	struct MainBufferF : public ::Buffer::Array
	{
		::Attribute::VectorF3	Pos;
		::Attribute::VectorF3	Tex;
		::Attribute::VectorF3	Normal;
		~MainBufferF();
		MainBufferF(::VertexArray & vertex_array);
	};
	struct MainBufferU : public ::Buffer::Array
	{
		::Attribute::UInt	Value;
		~MainBufferU();
		MainBufferU(::VertexArray & vertex_array);
	};
};

#endif