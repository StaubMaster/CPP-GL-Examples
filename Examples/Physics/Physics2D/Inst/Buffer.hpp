#ifndef  PHYSICS_2D_INST_BUFFER_HPP
# define PHYSICS_2D_INST_BUFFER_HPP

# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Attribute/Point2D.hpp"

namespace Physics2D
{
namespace Inst
{
class Buffer : public ::Buffer::Attribute
{
	private:
	::Attribute::Point2D	Pos;
	::Attribute::Point2D	Vel;
	public:
	Buffer(
		unsigned int indexPos,
		unsigned int indexVel
	);
};
};
};

#endif