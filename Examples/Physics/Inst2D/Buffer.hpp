#ifndef  INST_2D_BUFFER_HPP
# define INST_2D_BUFFER_HPP

# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Attribute/Trans2D.hpp"

namespace Inst2D
{
class Buffer : public ::Buffer::Attribute
{
	public:
	::Attribute::Trans2D	Now;
	public:
	Buffer(BufferArray::Base & buffer_array);
};
};

#endif