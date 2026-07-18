#ifndef  UI_CONTROL_GRAPH_HPP
# define UI_CONTROL_GRAPH_HPP

# include "Control/General/Base.hpp"

# include "../Miscellaneous/Telemetry/ValueAccumulator.hpp"

# include "Graph/Object.hpp"

namespace UI
{

namespace Control
{

class Graph : public Base
{
	// multiple Lines per Graph
	// show Center Line
	// show Min/Max/Avg

	public:
	float	Center;
	float	Magnitude;

	public:
	ValueAccumulator<float>		Values;
	UI::Graph::Object			GraphObject;

	public:
	~Graph();
	Graph();

	public:
	void	RelayUpdateBox() override;
	void	RelayInsertObject() override;
	void	RelayRemoveObject() override;

};

};

};

#endif