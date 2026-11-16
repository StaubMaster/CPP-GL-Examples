#include "Control_Base.hpp"



UI::Control_Base * UI::Control_Base::Parent() const
{
	return Parent_;
}

void UI::Control_Base::ChildClear()
{
	Control_Container::ChildClear();
	AutoAnchorUpdateRequest();
}
void UI::Control_Base::ChildRemove(Control_Base & control)
{
	Control_Container::ChildRemove(control);
	AutoAnchorUpdateRequest();
}
void UI::Control_Base::ChildInsert(Control_Base & control)
{
	Control_Container::ChildInsert(control);
	control.Parent_ = this;

	control.DisplayUpdateRequest();
	control.AnchorUpdateRequest();
	AutoAnchorUpdateRequest();
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
