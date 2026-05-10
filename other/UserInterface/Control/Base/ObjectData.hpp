#ifndef  UI_CONTROL_OBJECT_DATA_HPP
# define UI_CONTROL_OBJECT_DATA_HPP

# include "ValueType/Box/F2.hpp"
# include "ValueType/ColorF4.hpp"

namespace UI
{
namespace Control
{
struct ObjectData
{
	bool	Remove;
	bool	Display;

	BoxF2	Box;
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