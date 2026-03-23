#ifndef  GRAPHICS_2D_INST_BUFFER_HPP
# define GRAPHICS_2D_INST_BUFFER_HPP

# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Attribute/Trans2D.hpp"

namespace Graphics2D
{
namespace Inst
{
class Buffer : public ::Buffer::Attribute
{
	public:
	::Attribute::Trans2D	Now;
	public:
	Buffer(BufferArray::Base & buffer_array);
};
};
};

#endif