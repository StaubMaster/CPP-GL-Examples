#include "Control_Base.hpp"
#include "Control/Window.hpp"



UI::Control_Base * UI::Control_Base::Parent() const
{
	return Parent_;
}

void UI::Control_Base::ChildClear()
{
	Control_Container::ChildClear();
	AutoAnchorUpdateRequest();
	if (_Window() != nullptr) { _Window() -> DepthCalculateRequest(); }
}
void UI::Control_Base::ChildRemove(Control_Base & control)
{
	Control_Container::ChildRemove(control);
	AutoAnchorUpdateRequest();
	if (_Window() != nullptr) { _Window() -> DepthCalculateRequest(); }
}
void UI::Control_Base::ChildInsert(Control_Base & control)
{
	Control_Container::ChildInsert(control);
	control.Parent_ = this;

	control.DisplayUpdateRequest();
	control.AnchorUpdateRequest();
	AutoAnchorUpdateRequest();
	if (_Window() != nullptr) { _Window() -> DepthCalculateRequest(); }
}

#include "Display/DisplayPosition.hpp"
bool UI::Control_Base::Check(const DisplayPosition & display_pos) const
{
	if (!IsThisVisible()) { return false; }
	if (!IsEnabled()) { return false; }

	const VectorF2 & pos = display_pos.Buffer.Corner;
	if (!BoxDisplay().ContainsExclusive(pos).All(true)) { return false; }

	return true;
}
UI::Control_Base * UI::Control_Base::Find(const DisplayPosition & display_pos)
{
	if (!Check(display_pos)) { return nullptr; }

	Control_Base * control = nullptr;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Control_Base * c = Children[i] -> Find(display_pos);
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

bool UI::Control_Base::IsHovering() const
{
	return (_Window() != nullptr) && (_Window() -> Hovering() == this);
}



bool UI::Control_Base::IsVisible() const
{
	if (!IsThisVisible()) { return false; }
	if (Parent_ != nullptr) { return Parent_ -> IsVisible(); }
	return true; // should this return true or false
	// a form in a window has no parent, so it should return true
	// but a control that is nowhere cannot be displayed at all, so it should return false ?
}
void UI::Control_Base::Show()
{
	Control_Display::Show();
	if (Parent_ != nullptr) { Parent_ -> AutoAnchorUpdateRequest(); }
}
void UI::Control_Base::Hide()
{
	Control_Display::Hide();
	if (Parent_ != nullptr) { Parent_ -> AutoAnchorUpdateRequest(); }
}



ColorF4 UI::Control_Base::Color() const
{
	return ColorDefault;
}



unsigned int UI::Control_Base::Layer() const
{
	if (Parent_ != nullptr)
	{
		return (Parent_ -> Layer()) + 1;
	}
	else
	{
		return 0;
	}
}
unsigned int UI::Control_Base::LayerLimit() const
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
float UI::Control_Base::Depth(float depth) const
{
	depth = depth + Layer();
	depth = depth * LayerDepth();
	depth = depth + DepthOffset();
	return depth;
}



void UI::Control_Base::AnchorUpdate()
{
	Control_Display::AnchorUpdate();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> AnchorUpdateRequest();
	}
}

void UI::Control_Base::AutoAnchorUpdate_Y_StackMin()
{
	Control_Base * control = nullptr;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (Children[i] == nullptr) { continue; }
		Control_Base & c = *Children[i];
		if (!c.IsVisible()) { continue; }
		c.Make_Anchor_Y_Min(control);
		control = &c;
	}
	AnchorUpdateRequest();
}



#include "UIManager.hpp"
#include "Control/Graphics/Inst/Data.hpp"
void UI::Control_Base::DisplayPut() const
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
void UI::Control_Base::DisplayPutRecursive() const
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

void UI::Control_Base::DisplayUpdate()
{
	Control_Display::DisplayUpdate();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> DisplayUpdateRequest();
		// AutoAnchorUpdateRequest() ?
	}
}



void UI::Control_Base::UpdateRecursive()
{
	Update();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateRecursive();
	}
}
