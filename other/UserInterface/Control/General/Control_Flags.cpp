#include "Control_Flags.hpp"



bool UI::Control_Flags::IsEnabled() const
{
	return IsEnabled_;
}
void UI::Control_Flags::Enable()
{
	IsEnabled_ = true;
	//ColorUpdateRequestRecursive();
}
void UI::Control_Flags::Disable()
{
	IsEnabled_ = false;
	//ColorUpdateRequestRecursive();
}

bool UI::Control_Flags::IsOpaque() const
{
	return IsOpaque_;
}
void UI::Control_Flags::MakeTransparent()
{
	IsOpaque_ = false;
}
void UI::Control_Flags::MakeOpaque()
{
	IsOpaque_ = true;
}

bool UI::Control_Flags::IsThisVisible() const
{
	return IsVisible_;
}
bool UI::Control_Flags::IsVisible() const
{
	return IsThisVisible();
}
void UI::Control_Flags::Show()
{
	IsVisible_ = true;
}
void UI::Control_Flags::Hide()
{
	IsVisible_ = false;
}

bool UI::Control_Flags::IsDisplay() const
{
	return IsOpaque() && IsVisible();
}
/*bool UI::Control_Flags::IsThisInteractible() const
{
	return IsEnabled() && IsDisplay();
}*/
bool UI::Control_Flags::IsInteractible() const
{
	return IsEnabled() && IsVisible();
}
