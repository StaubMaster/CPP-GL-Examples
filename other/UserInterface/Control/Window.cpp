#include "Control/Window.hpp"



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
UI::Control::Window::~Window()
{ }



void UI::Control::Window::UpdateWindowSize(VectorF2 size)
{
	BoxDisplay = BoxF2(VectorF2(), size);
	BoxBoarder = BoxDisplay;
	BoxContent = BoxDisplay;
	BoxUpdateRequest();
}

#include <iostream>
void UI::Control::Window::UpdateDepth()
{
	unsigned int layer_sum = 0;
	for (unsigned int i = 0; i < Children.Count(); i++) // Assumes Window only holds Forms
	{
		const Base * control = Children[i];
		if (control == nullptr) { continue; }
		layer_sum += control -> LayerLimit();
	}
	std::cout << "LayerSum: " << layer_sum << '\n';

	float depth_size = 1.0f / (layer_sum + 2);
	float depth_offset = depth_size;

	std::cout << "DepthSize: " << depth_size << '\n';
	for (unsigned int i = 0; i < Children.Count(); i++) // Assumes Window only holds Forms
	{
		Base * control = Children[i];
		if (control == nullptr) { continue; }
		control -> AssignDepth(depth_offset, depth_size, 0);
		depth_offset += control -> LayerLimit() * depth_size;
	}
	std::cout << '\n';
}