#include "Control/Window.hpp"



void UI::Control::Window::AssignPointers(Base & control)
{
	control.Parent = this;
	control.AssignPointerRecursive(Manager);
	control.AssignPointerRecursive(this);
}



#include <iostream>
#include "Control/Form.hpp"
/*void UI::Control::Window::DepthUpdate()
{
	unsigned int layer_sum = 0;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		const UI::Control::Form * form = dynamic_cast<const UI::Control::Form*>(Children[i]);
		if (form == nullptr) { continue; }

		unsigned int limit = form -> LayerLimit();
		limit = limit + 1;
		std::cout << "limit: " << limit << '\n';
		layer_sum += limit;
	}
	std::cout << "LayerSum: " << layer_sum << '\n';

	float depth_size = 1.0f / (layer_sum + 2);
	DepthSize = depth_size;
	std::cout << "DepthSize: " << depth_size << '\n';

	float depth_offset = depth_size;
	std::cout << "DepthOffset: " << depth_offset << '\n';
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		UI::Control::Form * form = dynamic_cast<UI::Control::Form*>(Children[i]);
		if (form == nullptr) { continue; }
		unsigned int limit = form -> LayerLimit();
		form -> DepthOffset = depth_offset;
		depth_offset += limit * depth_size;
		std::cout << "DepthOffset: " << (form -> DepthOffset) << " to " << (depth_offset) << ' ' << limit << '\n';
	}
	std::cout << '\n';
}*/
float UI::Control::Window::Depth() const
{
	return 0.0f;
}



UI::Control::Window::~Window()
{ }
UI::Control::Window::Window()
{
	Anchor.X.Anchor = AnchorType::Both;
	Anchor.Y.Anchor = AnchorType::Both;
	AnchorDist.Min = VectorF2(0, 0);
	AnchorDist.Max = VectorF2(0, 0);
	ColorDefault = ColorF4(0, 0, 0);
	ColorHover = ColorF4(0, 0, 0);
	MakeTransparent();
}



void UI::Control::Window::BoxUpdate()
{
	BoxDisplay = BoxF2(VectorF2(), WindowSize);
	BoxBoarder = BoxDisplay;
	BoxContent = BoxDisplay;
}



void UI::Control::Window::WindowPutDisplay()
{
	DisplayPutRecursive();
}



void UI::Control::Window::DepthCalculateResolve()
{
	if (DepthCalculateIsRequested)
	{
		DepthCalculate();
		DepthCalculateIsRequested = false;
	}
}
void UI::Control::Window::DepthCalculateRequest()
{
	DepthCalculateIsRequested = true;
}
void UI::Control::Window::DepthCalculate()
{
	unsigned int layer_sum = 0;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		const UI::Control::Form * form = dynamic_cast<const UI::Control::Form*>(Children[i]);
		if (form == nullptr) { continue; }

		unsigned int limit = form -> LayerLimit();
		limit = limit + 1;
		std::cout << "limit: " << limit << '\n';
		layer_sum += limit;
	}
	std::cout << "LayerSum: " << layer_sum << '\n';

	float depth_size = 1.0f / (layer_sum + 2);
	DepthSize = depth_size;
	std::cout << "DepthSize: " << depth_size << '\n';

	float depth_offset = depth_size;
	std::cout << "DepthOffset: " << depth_offset << '\n';
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		UI::Control::Form * form = dynamic_cast<UI::Control::Form*>(Children[i]);
		if (form == nullptr) { continue; }
		unsigned int limit = form -> LayerLimit();
		form -> DepthOffset = depth_offset;
		depth_offset += limit * depth_size;
		std::cout << "DepthOffset: " << (form -> DepthOffset) << " to " << (depth_offset) << ' ' << limit << '\n';
	}
	std::cout << '\n';

	//LayerUpdateRecursive();
	//AssignDepthRecursive();
}
