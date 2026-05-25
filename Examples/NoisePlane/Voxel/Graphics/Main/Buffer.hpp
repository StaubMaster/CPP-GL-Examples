#ifndef  VOXEL_GRAPHICS_MAIN_BUFFER_HPP
# define VOXEL_GRAPHICS_MAIN_BUFFER_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Attribute/Layout.hpp"
# include "Graphics/Attribute/_Include.hpp"

namespace VoxelGraphics
{
	struct MainBufferF : public ::Buffer::Array
	{
		~MainBufferF();
		MainBufferF(::VertexArray & vertex_array);
	};
	struct MainLayoutF : public ::Attribute::Layout
	{
		::Attribute::VectorF3	Pos;
		::Attribute::VectorF3	Tex;
		::Attribute::VectorF3	Normal;
		~MainLayoutF();
		MainLayoutF();
	};
	struct MainBufferU : public ::Buffer::Array
	{
		~MainBufferU();
		MainBufferU(::VertexArray & vertex_array);
	};
	struct MainLayoutU : public ::Attribute::Layout
	{
		::Attribute::UInt		Voxel;
		::Attribute::UInt		Texture;
		::Attribute::VectorI3	Chunk;
		~MainLayoutU();
		MainLayoutU();
	};
};

#endif