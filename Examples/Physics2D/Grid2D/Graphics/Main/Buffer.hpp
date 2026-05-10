#ifndef  GRID_2D_GRAPHICS_MAIN_BUFFER_HPP
# define GRID_2D_GRAPHICS_MAIN_BUFFER_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Attribute/VectorF2.hpp"

namespace Grid2DGraphics
{
namespace Main
{
struct Buffer : public ::Buffer::Array
{
	public:
	::Attribute::VectorF2	Pos;
	public:
	~Buffer();
	Buffer(VertexArray & vertex_array);
};
};
};

#endif