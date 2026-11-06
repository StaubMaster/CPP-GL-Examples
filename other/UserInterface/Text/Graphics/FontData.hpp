#ifndef  UI_TEXT_FONT_DATA_HPP
# define UI_TEXT_FONT_DATA_HPP

# include "ValueType/Box/F2.hpp"

namespace UI
{
namespace Text
{
struct FontBufferData
{
	const static unsigned int	Limit = 128;
	BoxF2	Array[Limit];
};
};
};

#endif