#ifndef  UI_TEXT_FONT_DATA_HPP
# define UI_TEXT_FONT_DATA_HPP

# include "ValueType/Box/F2.hpp"

namespace UI
{

namespace Text
{

const static unsigned int	PalletsLimit = 128;

struct FontBufferData
{
	BoxF2	Array[PalletsLimit];
};

};

};

#endif