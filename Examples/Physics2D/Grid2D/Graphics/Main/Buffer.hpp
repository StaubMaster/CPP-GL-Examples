#ifndef  GRID_2D_GRAPHICS_MAIN_BUFFER_HPP
# define GRID_2D_GRAPHICS_MAIN_BUFFER_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Attribute/Point2D.hpp"

namespace Grid2DGraphics
{
namespace Main
{
struct Buffer : public ::Buffer::Array
{
	public:
	::Attribute::Point2D	Pos;
	public:
	~Buffer();
	Buffer(VertexArray & vertex_array);
};
};
};

#endif