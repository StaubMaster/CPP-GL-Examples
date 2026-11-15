#include "Control_Display.hpp"
#include "Control/Form.hpp"
#include "UIManager.hpp"
#include "Control/Graphics/Inst/Data.hpp"



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



/*unsigned int UI::Control_Display::Layer() const
{
	return Layer_;
}*/
/*void UI::Control_Display::LayerUpdate()
{
	if (Parent != nullptr)
	{
		Layer_ = (Parent -> Layer()) + 1;
	}
	else
	{
		Layer_ = 0;
	}
}*/
/*void UI::Control_Display::LayerUpdateRecursive()
{
	LayerUpdate();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> LayerUpdateRecursive();
	}
}*/

/*float UI::Control_Display::Depth() const
{
	return Depth_;
}*/
/*void UI::Control_Display::DepthUpdate()
{
	if (Window == nullptr) { return; }
	if (Form == nullptr) { return; }

	float size = Window -> DepthSize;
	float offset = Form -> DepthOffset;
	float layer = Layer();

	Depth_ = -((layer * size) + offset);
}*/
/*void UI::Control_Display::DepthUpdateRecursive()
{
	DepthUpdate();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> DepthUpdateRecursive();
	}
}*/
/*float UI::Control_Display::Depth() const
{
	// return NaN ?
	if (Window == nullptr) { return 0.0f; }
	if (Form == nullptr) { return 0.0f; }
	return -((Layer() * (Window -> DepthSize)) + (Form -> DepthOffset));
}*/
/*float UI::Control_Display::Depth(float diff) const
{
	if (_Window() == nullptr) { return 0.0f; }
	if (_Form() == nullptr) { return 0.0f; }
	float depth;
	depth = diff;
	depth = depth + (Layer());
	//Form.Depth(depth)
	//{
	depth = depth * (_Window() -> DepthSize);
	depth = depth + (_Form() -> DepthOffset);
	//}
	// put this Calculation in Form ?
	return -depth;
}*/



/*void UI::Control_Display::ColorUpdateRequest()
{
	ColorUpdateIsRequested = true;
}*/
/*void UI::Control_Display::ColorUpdate()
{
	if (Manager == nullptr)
	{
		Color = ColorDefault;
	}
	else
	{
		if (Manager -> Hovering != this)
		{
			Color = ColorDefault;
		}
		else
		{
			Color = ColorHover;
		}
	}
	ColorUpdateIsRequested = false;
}*/



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
