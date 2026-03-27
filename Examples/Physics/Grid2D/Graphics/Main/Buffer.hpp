#ifndef  GRID_2D_GRAPHICS_MAIN_BUFFER_HPP
# define GRID_2D_GRAPHICS_MAIN_BUFFER_HPP

# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Attribute/Point2D.hpp"

namespace Grid2DGraphics
{
namespace Main
{
struct Buffer : public ::Buffer::Attribute
{
	public:
	::Attribute::Point2D	Pos;
	public:
	~Buffer();
	Buffer(BufferArray::Base & buffer_array);
};
};
};

#endif