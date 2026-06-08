#ifndef  UI_GRAPH_OBJECT_DATA_HPP
# define UI_GRAPH_OBJECT_DATA_HPP

# include "ValueType/Box/F2.hpp"
# include "ValueType/ColorF4.hpp"

# include "../../Examples/General/Telemetry/ValueAccumulator.hpp"

namespace UI
{
namespace Graph
{
struct ObjectData
{
	bool	Remove;
	bool	Display;

	BoxF2		Box;
	float		Center;
	float		Magnitede;
	ColorF4		Col;

	ValueAccumulator<float> *	Values;

	~ObjectData();
	ObjectData();
	ObjectData(const ObjectData & other);
	ObjectData & operator=(const ObjectData & other);
};
};
};

#endif