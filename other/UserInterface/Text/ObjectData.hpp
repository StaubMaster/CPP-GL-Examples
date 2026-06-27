#ifndef  UI_TEXT_OBJECT_DATA_HPP
# define UI_TEXT_OBJECT_DATA_HPP

# include "Alignment.hpp"

# include "ValueType/Vector/F2.hpp"
# include "ValueType/Box/F2.hpp"
# include "ValueType/Color/F4.hpp"

# include <string>

namespace UI
{
namespace Text
{
struct ObjectData
{
	bool	Remove;
	bool	Display;
	// Object. to set Data to null when this gets deleted

	std::string		Text;
	VectorF2		TextPosition;
	Alignment		TextAlignmentX;
	Alignment		TextAlignmentY;

	VectorF2		CharacterSize;
	Alignment		CharacterAlignmentX;
	Alignment		CharacterAlignmentY;

	BoxF2			Bound;
	ColorF4			Color;

	bool			DisplayTextCursor;
	unsigned int	TextCursorIndex;

	~ObjectData();
	ObjectData();
	ObjectData(const ObjectData & other);
	ObjectData & operator=(const ObjectData & other);
};
};
};

#endif