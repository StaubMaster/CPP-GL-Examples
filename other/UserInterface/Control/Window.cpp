#include "Control/Window.hpp"
#include "Display/DisplaySize.hpp"
#include "AnchorEnum.hpp"



		UI::Manager *			UI::Control::Window::_Manager()			{ return Manager_; }
		UI::Manager *			UI::Control::Window::_Manager()	const	{ return Manager_; }
		UI::Control::Window *	UI::Control::Window::_Window()			{ return this; }
const	UI::Control::Window *	UI::Control::Window::_Window()	const	{ return this; }
		UI::Control::Form *		UI::Control::Window::_Form()			{ return nullptr; }
const	UI::Control::Form *		UI::Control::Window::_Form()	const	{ return nullptr; }

#include "Control/Form.hpp"
void UI::Control::Window::AssignPointers(Form & control)
{
	control.Window_ = this;
	//control.AssignPointerRecursive(Manager);
	//control.AssignPointerRecursive(this);
}



void UI::Control::Window::ChildClear()
{
	Children.Clear();
	//AutoAnchorUpdateRequest();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> AutoAnchorUpdateRequest();
	}
}
void UI::Control::Window::ChildRemove(Form & control)
{
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (Children[i] == &control)
		{
			Children.RemoveAt(i);
			i--;
		}
	}
	//AutoAnchorUpdateRequest();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> AutoAnchorUpdateRequest();
	}
}
void UI::Control::Window::ChildInsert(Form & control)
{
	AssignPointers(control);
	Children.Insert(&control);

	control.DisplayUpdateRequest();

	control.AnchorUpdateRequest();

	//control.BoxUpdateRequestRecursive();

	//control.ColorUpdateRequestRecursive();

	//AutoAnchorUpdateRequest();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> AutoAnchorUpdateRequest();
	}
}

void UI::Control::Window::ChildRemove(Form * control)
{
	if (control != nullptr)
	{
		ChildRemove(*control);
	}
}
void UI::Control::Window::ChildInsert(Form * control)
{
	if (control != nullptr)
	{
		ChildInsert(*control);
	}
}



void UI::Control::Window::SizeChange(const DisplaySize & display_size)
{
	Size = display_size.Buffer.Full;
	//AnchorUpdateRequest();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> AnchorUpdateRequest();
	}
}



#include <iostream>
#include "Control/Form.hpp"
void UI::Control::Window::DepthCalculateRequest()
{
	DepthCalculateIsRequested = true;
}
/*void UI::Control::Window::DepthCalculateResolve()
{
	if (DepthCalculateIsRequested)
	{
		DepthCalculate();
	}
}*/
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

	DepthCalculateIsRequested = false;
}



BoxF2 UI::Control::Window::BoxDisplay() const { return BoxF2(VectorF2(), Size); }
BoxF2 UI::Control::Window::BoxBoarder() const { return BoxDisplay(); }
BoxF2 UI::Control::Window::BoxContent() const { return BoxBoarder(); }



void UI::Control::Window::DisplayPut()
{
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> DisplayPutRecursive();
	}
}
void UI::Control::Window::Update()
{
	//DepthCalculateResolve();
	if (DepthCalculateIsRequested) { DepthCalculate(); }

	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateRecursive();
	}
}



UI::Control::Window::Window()
{
//	Anchor.X.Anchor = AnchorType::Both;
//	Anchor.Y.Anchor = AnchorType::Both;
//	AnchorDist.Min = VectorF2(0, 0);
//	AnchorDist.Max = VectorF2(0, 0);
//	ColorDefault = ColorF4(0, 0, 0);
//	ColorHover = ColorF4(0, 0, 0);
//	MakeTransparent();
}



UI::Control::ControlDisplay * UI::Control::Window::FindHover(const VectorF2 & mouse)
{
	if (!BoxDisplay().ContainsExclusive(mouse).All(true)) { return nullptr; }

	// check BoxContent before checking children ?
	ControlDisplay * control = nullptr;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		ControlDisplay * c = Children[i] -> FindHover(mouse);
		if (c == nullptr) { continue; }
		if (control == nullptr || ((c -> Depth()) < (control -> Depth())))
		{
			control = c;
		}
	}
	if (control != nullptr)
	{
		return control;
	}
	return nullptr;
}
