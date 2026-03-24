#ifndef  GRAPHICS_2D_WIRE_BUFFER_HPP
# define GRAPHICS_2D_WIRE_BUFFER_HPP

# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Buffer/Element.hpp"
# include "Graphics/Attribute/Point2D.hpp"
# include "Graphics/Attribute/ColorF4.hpp"

namespace Graphics2D
{
namespace Wire
{
namespace Main
{
class Buffer : public ::Buffer::Attribute
{
	public:
	::Attribute::Point2D	Pos;
	::Attribute::ColorF4	Col;
	public:
	~Buffer();
	Buffer(BufferArray::Base & buffer_array);
};
};
namespace Elem
{
class Buffer : public ::Buffer::Element
{
	public:
	~Buffer();
	Buffer(BufferArray::Base & buffer_array);
};
};
};
};

#endif