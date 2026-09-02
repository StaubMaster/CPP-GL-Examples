#include "Control/Window.hpp"



void UI::Control::Window::ChangePointers(Base & control)
{
	control.Parent = this;
	control.ChangeManagerRecursive(Manager);
	control.ChangeManagerRecursive(this);
}



//#include <iostream>
#include "Control/Form.hpp"
void UI::Control::Window::AssignDepth()
{
	unsigned int layer_sum = 0;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		const UI::Control::Form * form = dynamic_cast<const UI::Control::Form*>(Children[i]);
		if (form == nullptr) { continue; }

		layer_sum += form -> LayerLimit();
	}
//	std::cout << "LayerSum: " << layer_sum << '\n';

	float depth_size = 1.0f / (layer_sum + 2);
	DepthSize = depth_size;
//	std::cout << "DepthSize: " << depth_size << '\n';

	float depth_offset = depth_size;
//	std::cout << "DepthOffset: " << depth_offset << '\n';
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		UI::Control::Form * form = dynamic_cast<UI::Control::Form*>(Children[i]);
		if (form == nullptr) { continue; }

		form -> DepthOffset = depth_offset;

		depth_offset += form -> LayerLimit() * depth_size;
//		std::cout << "DepthOffset: " << depth_offset << '\n';
	}
//	std::cout << '\n';
}



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

void UI::Control::Window::PutDisplay()
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
