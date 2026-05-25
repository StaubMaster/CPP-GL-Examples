#ifndef  VOXEL_GRAPHICS_BUFFER_HPP
# define VOXEL_GRAPHICS_BUFFER_HPP

# include "Main/Buffer.hpp"
# include "Inst/Buffer.hpp"

# include "Graphics/Buffer/MainInst.hpp"
# include "Graphics/Buffer/Main.hpp"

namespace VoxelGraphics
{
	typedef ::BufferArray::Main<
		GL::BufferDataUsage::DynamicDraw,
		GL::DrawMode::Triangles
	> BufferU;
	/*struct BufferU : public ::BufferArray::Main<MainBufferU>
	{
		~BufferU();
		BufferU();
	};*/
	typedef ::BufferArray::MainInst<
		GL::BufferDataUsage::DynamicDraw,
		GL::BufferDataUsage::StaticDraw,
		GL::DrawMode::Triangles
	> BufferF;
	/*struct BufferF : public ::BufferArray::MainInst<MainBufferF, InstBuffer>
	{
		~BufferF();
		BufferF();
	};*/
};

#endif