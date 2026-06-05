#ifndef  UI_GRAPH_OBJECT_DATA_HPP
# define UI_GRAPH_OBJECT_DATA_HPP

# include "ValueType/Box/F2.hpp"
# include "ValueType/ColorF4.hpp"

# include "../../Examples/Telemetry/ValueAccumulator.hpp"

namespace UI
{
namespace Graph
{
struct ObjectData
{
	bool	Remove;
	bool	Display;

	// each Object should contain
	// a Box of where the Graph is
	// an Array of Values
	// maybe some scaling info

	BoxF2						Box;
	ValueAccumulator<float> *	Values;
	ColorF4						Col;

	~ObjectData();
	ObjectData();
	ObjectData(const ObjectData & other);
	ObjectData & operator=(const ObjectData & other);
};
};
};

#endif