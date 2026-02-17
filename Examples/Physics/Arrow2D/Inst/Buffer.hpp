#ifndef  ARROW_2D_INST_BUFFER_HPP
# define ARROW_2D_INST_BUFFER_HPP

# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Attribute/Point2D.hpp"
# include "Graphics/Attribute/Base/FloatN.hpp"

namespace Arrow2D
{
namespace Inst
{
class Buffer : public ::Buffer::Attribute
{
	private:
	::Attribute::Point2D	Pos;
	::Attribute::Point2D	Dir;
	::Attribute::FloatN		Size;
	public:
	Buffer(
		unsigned int indexPos,
		unsigned int indexDir,
		unsigned int indexSize
	);
};
};
};

#endif