#include "Control/Window.hpp"
#include "Control/Form.hpp"
#include "Display/DisplaySize.hpp"
#include "AnchorEnum.hpp"



void UI::Control::Window::ChildClear()
{
	Control_Container::ChildClear();
	//AutoAnchorUpdateRequest();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> AutoAnchorUpdateRequest();
	}
}
void UI::Control::Window::ChildRemove(Form & control)
{
	Control_Container::ChildRemove(control);
	//AutoAnchorUpdateRequest();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> AutoAnchorUpdateRequest();
	}
}
void UI::Control::Window::ChildInsert(Form & control)
{
	Control_Container::ChildInsert(control);
	control.Window_ = this;

	control.DisplayUpdateRequest();
	control.AnchorUpdateRequest();
	//AutoAnchorUpdateRequest();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> AutoAnchorUpdateRequest();
	}
}


#include "Display/DisplayPosition.hpp"
#include "HoverArgs.hpp"
bool UI::Control::Window::Check(const DisplayPosition & display_pos) const
{
	const VectorF2 & pos = display_pos.Buffer.Corner;
	if (!Box().ContainsExclusive(pos).All(true)) { return false; }

	return true;
}
UI::Control::Form * UI::Control::Window::Find(const DisplayPosition & display_pos)
{
	if (!Check(display_pos)) { return nullptr; }

	Form * control = nullptr;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Form * c = Children[i];
		if (!c -> Check(display_pos)) { continue; }
		if (control == nullptr || ((c -> Depth()) > (control -> Depth())))
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

UI::Control::Form *  UI::Control::Window::Hovering() const { return Hovering_; }
UI::Control::Form *  UI::Control::Window::Selected() const { return Selected_; }
void UI::Control::Window::HoveringChange(UI::Control::Form * form, const DisplayPosition & display_pos)
{
	if (Hovering_ != form)
	{
		if (Hovering_ != nullptr) { Hovering_ -> RelayHover(HoverArgs(HoverType::Leave, display_pos)); }
		// Form.Hovering Relay Enter
		Hovering_ = form;
		// Form.Hovering Relay Leave
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
	LayerCount = 0;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		const UI::Control::Form * form = Children[i];
		if (form == nullptr) { continue; }

		unsigned int limit = form -> LayerLimit();
		std::cout << "limit: " << limit << "(+1)\n";
		LayerCount += limit + 1;
	}
	std::cout << "LayerCount: " << LayerCount << "(+2)\n";
	LayerCount += 2;

	LayerDepth = 1.0f / LayerCount;
	std::cout << "LayerDepth: " << LayerDepth << '\n';

	unsigned int layer_offset_0 = 1;
	unsigned int layer_offset_1;
	unsigned int layer_range;
	float depth_offset_0 = LayerDepth;
	float depth_offset_1;
	float depth_range;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		UI::Control::Form * form = Children[i];
		if (form == nullptr) { continue; }

		layer_range = form -> LayerLimit() + 1;
		depth_range = layer_range * LayerDepth;
		form -> DepthChange(depth_offset_0);

		layer_offset_1 = layer_offset_0 + layer_range;
		depth_offset_1 = depth_offset_0 + depth_range;
		std::cout << "Form Depth";
		std::cout << ' ' << "[" << (layer_offset_0) << " to " << (layer_offset_1) << "]";
		std::cout << ' ' << "{" << (depth_offset_0) << " to " << (depth_offset_1) << "}";
		std::cout << '\n';
		layer_offset_0 = layer_offset_1;
		depth_offset_0 = depth_offset_1;
	}
	std::cout << '\n';

	DepthCalculateIsRequested = false;
}
/* Depth
	in terms of the FrameBuffer: - is in front of +
*/

float UI::Control::Window::Depth(float depth) const
{
	return depth * LayerDepth;
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



#include "Control/General/Base.hpp"
// args
#include "User/MouseArgs.hpp"
#include "User/KeyBoardArgs.hpp"
#include "HoverArgs.hpp"
void UI::Control::Window::RelayMove(MoveArgs args)
{
	(void)args;
	//UpdateMouse(args.Position);
}
void UI::Control::Window::RelayHover(HoverArgs args)
{
	(void)args;
}
void UI::Control::Window::RelayClick(ClickArgs args)
{
	if (Hovering() != nullptr)
	{
		if (Hovering() -> Hovering() != nullptr)
		{
			Hovering() -> Hovering() -> RelayClick(args);
		}
	}
	SelectedUpdate();
}
void UI::Control::Window::RelayScroll(ScrollArgs args)
{
	/*
		try scroll on Hovering
		if no scroll
			try scroll Parent
			loop until scroll or no Parent
		if no Parent
			try scroll Selected
			if no scroll
				try scroll Parent
				loop until scroll or no Parent
	currently no way to determin if have scroll */

	if (Hovering() != nullptr)
	{
		UI::Control::Base * control = Hovering() -> Hovering();
		while (control != nullptr)
		{
			control -> RelayScroll(args);
			control = control -> Parent();
		}
	}

	if (Selected() != nullptr)
	{
		UI::Control::Base * control = Selected() -> Selected();
		while (control != nullptr)
		{
			control -> RelayScroll(args);
			control = control -> Parent();
		}
	}
}
void UI::Control::Window::RelayDrag(DragArgs args)
{
	if (Selected() != nullptr)
		Selected() -> RelayDrag(args);
}
#include <iostream>
#include "ValueType/_Show.hpp"
static void DisplayControlCountRecursive(const UI::Control::Base & control)
{
	std::cout << control.Children.Count();
	std::cout << ' ';
	std::cout << control.Depth();
	std::cout << '\n';
	if (control.Children.Count() == 0) { return; }
	std::cout << "[\n";
	for (unsigned int i = 0; i < control.Children.Count(); i++)
	{
		DisplayControlCountRecursive(*control.Children[i]);
	}
	std::cout << "]\n";
}
void UI::Control::Window::RelayKey(KeyArgs args)
{
	if (Selected() != nullptr)
		Selected() -> RelayKey(args);

	if (args.Key == Keys::Enter && args.Action == Action::Press)
	{
		if (Hovering() != nullptr)
		{
			const UI::Control::Form & form = *Hovering();
			std::cout << "Form Depth: " << (form.Depth_) << '\n';
			if (form.Hovering() != nullptr)
			{
				std::cout << "Control Depth: " << (form.Hovering() -> Depth()) << '\n';
			}
			std::cout << "Form Children: " << (form.Children.Count()) << '\n';
			for (unsigned int i = 0; i < form.Children.Count(); i++)
			{
				DisplayControlCountRecursive(*form.Children[i]);
			}
		}
	}
}
void UI::Control::Window::RelayText(TextArgs args)
{
	if (Selected() != nullptr)
		Selected() -> RelayText(args);
}
