#ifndef  USER_INTERFACE_TEST_GRAPH_HPP
# define USER_INTERFACE_TEST_GRAPH_HPP

# include "Control/_Include.hpp"

struct TestGraph : public UI::Control_::Form
{
	//UI::Control_::GroupBox	SliderGroupBox;
	//UI::Control_::Slider		SliderHori;
	//UI::Control_::Slider		SliderVert;
	//UI::Control_::Slider		SliderArea;

	UI::Control_::Slider	SliderArea;

	UI::Control_::Graph		GraphHori;
	UI::Control_::Graph		GraphVert;

	TestGraph();

	void	SliderHoriChange(VectorF2 val);
	void	SliderVertChange(VectorF2 val);
	void	SliderAreaChange(VectorF2 val);
};

#endif