#ifndef  POLYHEDRA_GRAPHICS_WIRE_ELEM_BUFFER_HPP
# define POLYHEDRA_GRAPHICS_WIRE_ELEM_BUFFER_HPP

# include "Graphics/Buffer/Element.hpp"

namespace PolyHedraWire
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