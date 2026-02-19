#ifndef  ARROW_2D_INST_BUFFER_HPP
# define ARROW_2D_INST_BUFFER_HPP

# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Attribute/Point2D.hpp"
# include "Graphics/Attribute/ColorF4.hpp"
# include "Graphics/Attribute/Base/FloatN.hpp"

namespace Arrow2D
{
namespace Inst
{
class Buffer : public ::Buffer::Attribute
{
	private:
	::Attribute::Point2D	Pos0;
	::Attribute::Point2D	Pos1;
	::Attribute::FloatN		Size;
	::Attribute::ColorF4	Col;
	public:
	Buffer(
		BufferArray::Base & buffer_array,
		unsigned int indexPos0,
		unsigned int indexPos1,
		unsigned int indexSize,
		unsigned int indexCol
	);
};
};
};

#endif