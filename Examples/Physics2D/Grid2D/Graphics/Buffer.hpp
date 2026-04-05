#ifndef  GRID_2D_GRAPHICS_BUFFER_HPP
# define GRID_2D_GRAPHICS_BUFFER_HPP

# include "Graphics/Buffer/MainElemInst.hpp"
# include "Grid2D/Graphics/Main/Buffer.hpp"
# include "Grid2D/Graphics/Elem/Buffer.hpp"
# include "Grid2D/Graphics/Inst/Buffer.hpp"

namespace Grid2DGraphics
{
typedef ::BufferArray::MainElemInst<
	Grid2DGraphics::Main::Buffer,
	Grid2DGraphics::Elem::Buffer,
	Grid2DGraphics::Inst::Buffer
> Buffer;
};

#endif