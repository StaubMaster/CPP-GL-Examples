#ifndef  UI_TEXT_OBJECT_DATA_HPP
# define UI_TEXT_OBJECT_DATA_HPP

# include "Alignment.hpp"

# include "ValueType/Point2D.hpp"
# include "ValueType/AxisBox2D.hpp"
# include "ValueType/ColorF4.hpp"

# include <string>

namespace UI
{
namespace Text
{
struct ObjectData
{
	std::string		Text;
	Point2D			TextPosition;
	Alignment		TextAlignmentX;
	Alignment		TextAlignmentY;

	Point2D		CharacterSize;
	Alignment	CharacterAlignmentX;
	Alignment	CharacterAlignmentY;

	AxisBox2D	Bound;
	ColorF4		Color;

	bool	Remove;
	bool	Display;

	~ObjectData();
	ObjectData();
	ObjectData(const ObjectData & other);
	ObjectData & operator=(const ObjectData & other);
};
};
};

#endif