#ifndef  POLYGON_GRAPHICS_WIRE_ELEM_BUFFER_HPP
# define POLYGON_GRAPHICS_WIRE_ELEM_BUFFER_HPP

# include "Graphics/Buffer/Element.hpp"

namespace PolyGonWire
{
namespace Elem
{
class Buffer : public ::Buffer::Element
{
	public:
	~Buffer();
	Buffer(BufferArray::Base & buffer_array, unsigned int elem_per_type);
};
};
};

#endif