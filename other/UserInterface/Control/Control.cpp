#include "Control.hpp"
#include "Control/Form.hpp"
#include "Control/Window.hpp"



		UI::Manager *			UI::Control::_Manager()			{ if (Parent_ == nullptr) { return nullptr; } return Parent_ -> _Manager(); }
		UI::Manager *			UI::Control::_Manager()	const	{ if (Parent_ == nullptr) { return nullptr; } return Parent_ -> _Manager(); }
		UI::Control_::Window *	UI::Control::_Window()			{ if (Parent_ == nullptr) { return nullptr; } return Parent_ -> _Window(); }
const	UI::Control_::Window *	UI::Control::_Window()	const	{ if (Parent_ == nullptr) { return nullptr; } return Parent_ -> _Window(); }
		UI::Control_::Form *	UI::Control::_Form()			{ if (Parent_ == nullptr) { return nullptr; } return Parent_ -> _Form(); }
const	UI::Control_::Form *	UI::Control::_Form()	const	{ if (Parent_ == nullptr) { return nullptr; } return Parent_ -> _Form(); }

UI::Control * UI::Control::Parent() const
{
	return Parent_;
}

void UI::Control::ChildClear()
{
	Control_Container::ChildClear();
	AutoAnchorUpdateRequest();
	if (_Window() != nullptr) { _Window() -> DepthCalculateRequest(); }
}
void UI::Control::ChildRemove(Control & control)
{
	Control_Container::ChildRemove(control);
	AutoAnchorUpdateRequest();
	if (_Window() != nullptr) { _Window() -> DepthCalculateRequest(); }
}
void UI::Control::ChildInsert(Control & control)
{
	Control_Container::ChildInsert(control);
	control.Parent_ = this;
	control.DisplayUpdateRequest();
	control.AnchorUpdateRequest();

	AutoAnchorUpdateRequest();
	if (_Window() != nullptr) { _Window() -> DepthCalculateRequest(); }
}

#include "Display/DisplayPosition.hpp"
bool UI::Control::Check(const DisplayPosition & display_pos) const
{
	if (!IsThisVisible()) { return false; }
	if (!IsEnabled()) { return false; }

	const VectorF2 & pos = display_pos.Buffer.Corner;
	if (!BoxDisplay().ContainsExclusive(pos).All(true)) { return false; }

	return true;
}
UI::Control * UI::Control::Find(const DisplayPosition & display_pos)
{
	if (!Check(display_pos)) { return nullptr; }

	Control * control = nullptr;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Control * c = Children[i] -> Find(display_pos);
		if (c == nullptr) { continue; }
		if (control == nullptr || ((c -> Depth()) > (control -> Depth())))
		{
			control = c;
		}
	}
	if (control != nullptr)
	{
		return control;
	}
	return this;
}

bool UI::Control::IsHovering() const
{
	return (_Window() != nullptr) && (_Window() -> Hovering() == this);
}



bool UI::Control::IsVisible() const
{
	if (!IsThisVisible()) { return false; }
	if (Parent() != nullptr) { return Parent() -> IsVisible(); }
	return true; // should this return true or false
	// a form in a window has no parent, so it should return true
	// but a control that is nowhere cannot be displayed at all, so it should return false ?
}
void UI::Control::Show()
{
	Control_Display::Show();
	if (Parent() != nullptr) { Parent() -> AutoAnchorUpdateRequest(); }
	if (_Window() != nullptr) { _Window() -> DepthCalculateRequest(); }
}
void UI::Control::Hide()
{
	Control_Display::Hide();
	if (Parent() != nullptr) { Parent() -> AutoAnchorUpdateRequest(); }
	if (_Window() != nullptr) { _Window() -> DepthCalculateRequest(); }
}



ColorF4 UI::Control::Color() const
{
	return ColorDefault;
}



unsigned int UI::Control::Layer() const
{
	if (Parent() != nullptr) { return (Parent() -> Layer()) + 1; }
	return 0;
}
unsigned int UI::Control::LayerLimit() const
{
	if (Children.Count() != 0)
	{
		unsigned int limit = 0;
		for (unsigned int i = 0; i < Children.Count(); i++)
		{
			unsigned int l = Children[i] -> LayerLimit();
			if (l > limit) { limit = l; }
		}
		return limit + 1;
	}
	return 0;
}
float UI::Control::Depth(float depth) const
{
	if (_Window() == nullptr) { return 0.0f; }
	if (_Form() == nullptr) { return 0.0f; }
	depth = depth + Layer();
	depth = depth * (_Window() -> LayerDepth());
	depth = depth + (_Form() -> DepthOffset());
	return depth;
}



void UI::Control::AnchorUpdate()
{
	Control_Display::AnchorUpdate();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> AnchorUpdateRequest();
	}
}

bool UI::Control::MetaIs() const
{
	return (Parent() != nullptr || _Window() != nullptr);
}
BoxF2 UI::Control::MetaBoxBoarder() const
{
	if (Parent() != nullptr) { return Parent() -> BoxBoarder(); }
	if (_Window() != nullptr) { return _Window() -> Box(); }
	return BoxF2();
}
BoxF2 UI::Control::MetaBoxContent() const
{
	if (Parent() != nullptr) { return Parent() -> BoxContent(); }
	if (_Window() != nullptr) { return _Window() -> Box(); }
	return BoxF2();
}

#include <iostream>
void UI::Control::AutoAnchorUpdate_Y_StackMin()
{
	std::cout << "AutoAnchor ....\n";
	Control * control = nullptr;
	std::cout << "Count " << Children.Count() << '\n';
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (!Children[i] -> IsThisVisible()) { continue; }
		std::cout << "control\n";
		Children[i] -> Make_Anchor_Y_Min(control);
		control = Children[i];
	}
	std::cout << "AutoAnchor done\n";
	AnchorUpdateRequest();
}
void UI::Control::AutoFitMinY()
{
	float val = 0.0f;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (!Children[i] -> IsThisVisible()) { continue; }
		float v = Children[i] -> MarginBox_Get_Y_Min_Max();
		if (v > val) { val = v; }
	}
	std::cout << "AutoFitMinY " << val << '\n';
	PaddingBox_Set_Y_Size(val);
	AnchorUpdateRequest();
}




#include "UIManager.hpp"
#include "Control/Graphics/Inst/Data.hpp"
void UI::Control::DisplayPut() const
{
	if (_Manager() != nullptr && MetaIs() && IsOpaque())
	{
		UI::ControlGraphics::Inst::Data data;
		data.Layer = -Depth();
		data.Box = BoxDisplay();
		data.Color = Color();
		data.Bound = MetaBoxBoarder();
		_Manager() -> ControlManager.InstancePut(data);
	}
}
void UI::Control::DisplayPutRecursive() const
{
	if (IsThisVisible())
	{
		DisplayPut();
		for (unsigned int i = 0; i < Children.Count(); i++)
		{
			Children[i] -> DisplayPutRecursive();
		}
	}
}

void UI::Control::DisplayUpdate()
{
	Control_Display::DisplayUpdate();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> DisplayUpdateRequest();
		// AutoAnchorUpdateRequest() ?
	}
}



void UI::Control::UpdateRecursive()
{
	Update();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateRecursive();
	}
}
