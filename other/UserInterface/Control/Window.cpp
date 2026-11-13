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
BoxF2 UI::Control::Window::Box() const
{
	return BoxF2(VectorF2(), Size);
}



#include "Display/DisplayPosition.hpp"
#include "HoverArgs.hpp"
UI::Control::Form * UI::Control::Window::Find(const DisplayPosition & display_pos)
{
	const VectorF2 & pos = display_pos.Buffer.Corner;

	if (!Box().ContainsExclusive(pos).All(true)) { return nullptr; }

	// check BoxContent before checking children ?
	Form * control = nullptr;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Form * c = Children[i];
		if (!c -> IsThisVisible()) { continue; }
		if (!c -> IsEnabled()) { continue; }
		if (!c -> BoxDisplay().ContainsExclusive(pos).All(true)) { continue; }
		if (control == nullptr || ((c -> Depth()) < (control -> Depth())))
		{
			control = c;
		}
		/*Form * c = Children[i] -> Find(display_pos);
		if (c == nullptr) { continue; }
		if (control == nullptr || ((c -> Depth()) < (control -> Depth())))
		{
			control = c;
		}*/
	}
	if (control != nullptr)
	{
		return control;
	}
	return nullptr;
}
UI::Control::Form *  UI::Control::Window::Hovering() const { return Hovering_; }
UI::Control::Form *  UI::Control::Window::Selected() const { return Selected_; }
void UI::Control::Window::HoveringChange(UI::Control::Form * form, const DisplayPosition & display_pos)
{
	if (Hovering_ != form)
	{
		if (Hovering_ != nullptr) { Hovering_ -> RelayHover(HoverArgs(HoverType::Leave, display_pos)); }
		Hovering_ = form;
		if (Hovering_ != nullptr) { Hovering_ -> RelayHover(HoverArgs(HoverType::Enter, display_pos)); }
	}
	else
	{
		if (Hovering_ != nullptr) { Hovering_ -> RelayHover(HoverArgs(HoverType::Move, display_pos)); }
	}
}
void UI::Control::Window::SelectedChange()
{
	Selected_ = Hovering_;
	if (Selected_ != nullptr)
	{
		Selected_ -> SelectedChange();
	}
}
void UI::Control::Window::HoveringUpdate(const DisplayPosition & display_pos)
{
	UI::Control::Form * form = Find(display_pos);
	HoveringChange(form, display_pos);
	if (form != nullptr)
	{
		form -> HoveringUpdate(display_pos);
	}
}
void UI::Control::Window::SelectedUpdate()
{
	SelectedChange();
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
