#ifndef  UI_CONTROL_GRAPH_HPP
# define UI_CONTROL_GRAPH_HPP

# include "Base/Base.hpp"

# include "../../Examples/Telemetry/ValueAccumulator.hpp"

namespace UI
{

namespace Control
{

class Graph : public Base
{
	ValueAccumulator<float>		Values;
	// Graph object ?
	// 

	public:
	~Graph();
	Graph();
};

};

};

#endif