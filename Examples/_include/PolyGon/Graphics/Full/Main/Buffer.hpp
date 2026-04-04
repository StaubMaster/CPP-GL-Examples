#ifndef  POLYGON_GRAPHICS_FULL_MAIN_BUFFER_HPP
# define POLYGON_GRAPHICS_FULL_MAIN_BUFFER_HPP

# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Attribute/Point2D.hpp"
# include "Graphics/Attribute/ColorF4.hpp"

namespace PolyGonFull
{
namespace Main
{
class Buffer : public ::Buffer::Attribute
{
	public:
	::Attribute::Point2D	Pos;
	::Attribute::ColorF4	Col;
	public:
	Buffer(BufferArray::Base & buffer_array);
};
};
};

#endif