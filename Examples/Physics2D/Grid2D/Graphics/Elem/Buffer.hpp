#ifndef  GRID_2D_GRAPHICS_ELEM_BUFFER_HPP
# define GRID_2D_GRAPHICS_ELEM_BUFFER_HPP

# include "Graphics/Buffer/Element.hpp"

namespace Grid2DGraphics
{
namespace Elem
{
struct Buffer : public ::Buffer::Element
{
	public:
	~Buffer();
	Buffer(BufferArray::Base & buffer_array, unsigned int elem_per_type);
};
};
};

#endif