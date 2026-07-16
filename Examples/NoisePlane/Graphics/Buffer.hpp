#ifndef  VOXEL_GRAPHICS_BUFFER_HPP
# define VOXEL_GRAPHICS_BUFFER_HPP

# include "Main/Buffer.hpp"
# include "Inst/Buffer.hpp"

# include "Graphics/VertexArray/Main.hpp"
# include "Graphics/VertexArray/MainInst.hpp"

namespace VoxelGraphics
{
	typedef ::VertexArray::Main BufferU;
	/*typedef ::VertexArray::Main<
		GL::BufferDataUsage::DynamicDraw,
		GL::DrawMode::Triangles
	> BufferU;*/
	typedef ::VertexArray::MainInst BufferF;
	/*typedef ::VertexArray::MainInst<
		GL::BufferDataUsage::DynamicDraw,
		GL::BufferDataUsage::StaticDraw,
		GL::DrawMode::Triangles
	> BufferF;*/
};

#endif