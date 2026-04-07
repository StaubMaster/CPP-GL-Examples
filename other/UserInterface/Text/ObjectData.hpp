#ifndef  UI_TEXT_OBJECT_DATA_HPP
# define UI_TEXT_OBJECT_DATA_HPP

# include "ValueType/Point2D.hpp"
# include "ValueType/AxisBox2D.hpp"

# include <string>

namespace UI
{
namespace Text
{
enum class Alignment
{
	Min,
	Mid,
	Max,
};

struct ObjectData
{
	std::string		Text;
	Alignment		AlignmentX;
	Alignment		AlignmentY;

	Point2D		Pos;
	AxisBox2D	Bound;

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