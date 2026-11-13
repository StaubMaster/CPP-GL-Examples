#ifndef  UI_CONTROL_GRAPH_HPP
# define UI_CONTROL_GRAPH_HPP

# include "Control/General/Base.hpp"

# include "../Miscellaneous/Telemetry/ValueAccumulator.hpp"

# include "Graph/Object.hpp"

namespace UI
{
namespace Control
{
class Graph : public Base // GraphLine
{
	// multiple Lines per Graph
	// show Center Line
	// show Min/Max/Avg

	// Hori / Vert
	// automatically calculate Center and Magniture

	public:
	float	Center = 64.0f;
	float	Magnitude = 8.0f;

	public:
	ValueAccumulator<float>		Values;
	UI::Graph::Object			GraphObject;

	public:
	Graph();

	public:
	void	Update() override;

	protected:
	void	RelayShow() override;
	void	RelayHide() override;

};
};
};

#endif