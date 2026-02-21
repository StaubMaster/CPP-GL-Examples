#ifndef  PHYSICS_2D_INST_BUFFER_HPP
# define PHYSICS_2D_INST_BUFFER_HPP

# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Attribute/Trans2D.hpp"

namespace Physics2D
{
namespace Inst
{
class Buffer : public ::Buffer::Attribute
{
	public:
	::Attribute::Trans2D	Now;
	::Attribute::Trans2D	Vel;
	public:
	Buffer(BufferArray::Base & buffer_array);
};
};
};

#endif