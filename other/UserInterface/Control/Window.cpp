#include "Control/Window.hpp"



void UI::Control::Window::ChangePointers(Base & control)
{
	control.Parent = this;
	control.ChangeManagerRecursive(Manager);
	control.ChangeManagerRecursive(this);
}



#include <iostream>
#include "Control/Form.hpp"
void UI::Control::Window::AssignDepth()
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
	_Opaque = false;
}



void UI::Control::Window::BoxUpdate()
{
	BoxDisplay = BoxF2(VectorF2(), WindowSize);
	BoxBoarder = BoxDisplay;
	BoxContent = BoxDisplay;

	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> BoxUpdateRequest();
	}
}



void UI::Control::Window::WindowPutDisplay()
{
	DisplayPutRecursive();
}



void UI::Control::Window::DepthUpdateResolve()
{
	if (DepthUpdateIsRequested)
	{
		DepthUpdate();
		DepthUpdateIsRequested = false;
	}
}
void UI::Control::Window::DepthUpdateRequest()
{
	DepthUpdateIsRequested = true;
}
void UI::Control::Window::DepthUpdate()
{
	CalcLayerRecursive();
	AssignDepthRecursive();
}
