#include "Control/General/Control_Display.hpp"
#include "Control/Form.hpp"



// put these in VisibleChanged() ?
void UI::Control_Display::MakeTransparent()
{
	Control_Flags::MakeTransparent();
	DisplayUpdateRequest();
}
void UI::Control_Display::MakeOpaque()
{
	Control_Flags::MakeOpaque();
	DisplayUpdateRequest();
}
void UI::Control_Display::Show()
{
	Control_Flags::Show();
	DisplayUpdateRequest();
}
void UI::Control_Display::Hide()
{
	Control_Flags::Hide();
	DisplayUpdateRequest();
}



void UI::Control_Display::DisplayUpdateRequest()
{
	DisplayUpdateIsRequested = true;
}
void UI::Control_Display::DisplayUpdate()
{
	if (IsDisplay())	{ RelayShow(); }
	else				{ RelayHide(); }

	DisplayUpdateIsRequested = false;
}

void UI::Control_Display::RelayShow() { }
void UI::Control_Display::RelayHide() { }



void UI::Control_Display::Update()
{
	//AutoAnchorUpdateResolve();
	if (AutoAnchorUpdateIsRequested)	{ AutoAnchorUpdate(); }

	//BoxUpdateResolve();

	//AnchorUpdateResolve();
	if (AnchorUpdateIsRequested)		{ AnchorUpdate(); }

	//ColorUpdateResolve();

	//DisplayUpdateResolve();
	if (DisplayUpdateIsRequested)		{ DisplayUpdate(); }
}
