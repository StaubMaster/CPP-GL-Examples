#ifndef  UI_CONTROL_OBJECT_DATA_HPP
# define UI_CONTROL_OBJECT_DATA_HPP

# include "ValueType/AxisBox2D.hpp"
# include "ValueType/ColorF4.hpp"

namespace UI
{
namespace Control
{
struct ObjectData
{
	bool	Remove;
	bool	Display;

	AxisBox2D	Box;
	float		Layer;
	ColorF4		Color;

	~ObjectData();
	ObjectData();
	ObjectData(const ObjectData & other);
	ObjectData & operator=(const ObjectData & other);
};
};
};

#endif