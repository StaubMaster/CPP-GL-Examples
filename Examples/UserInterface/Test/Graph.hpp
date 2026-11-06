#ifndef  USER_INTERFACE_TEST_GRAPH_HPP
# define USER_INTERFACE_TEST_GRAPH_HPP

# include "Control/_Include.hpp"

struct TestGraph : public UI::Control::Form
{
	//UI::Control::GroupBox	SliderGroupBox;
	//UI::Control::Slider		SliderHori;
	//UI::Control::Slider		SliderVert;
	//UI::Control::Slider		SliderArea;

	UI::Control::Slider		SliderArea;

	UI::Control::Graph		GraphHori;
	UI::Control::Graph		GraphVert;

	TestGraph();

	void	SliderHoriChange(VectorF2 val);
	void	SliderVertChange(VectorF2 val);
	void	SliderAreaChange(VectorF2 val);
};

#endif