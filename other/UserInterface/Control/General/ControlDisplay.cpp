#include "ControlDisplay.hpp"
#include "Control/Form.hpp"
#include "UIManager.hpp"
#include "Graphics/Inst/Data.hpp"



bool UI::Control::ControlDisplay::IsEnabled() const
{
	return IsEnabled_;
}
void UI::Control::ControlDisplay::Enable()
{
	IsEnabled_ = true;
	//ColorUpdateRequestRecursive();
}
void UI::Control::ControlDisplay::Disable()
{
	IsEnabled_ = false;
	//ColorUpdateRequestRecursive();
}

bool UI::Control::ControlDisplay::IsThisVisible() const
{
	return IsVisible_;
}
bool UI::Control::ControlDisplay::IsVisible() const
{
	return IsThisVisible();
}
void UI::Control::ControlDisplay::Show()
{
	IsVisible_ = true;
	DisplayUpdateRequest();
}
void UI::Control::ControlDisplay::Hide()
{
	IsVisible_ = false;
	DisplayUpdateRequest();
}

bool UI::Control::ControlDisplay::IsOpaque() const
{
	return IsOpaque_;
}
void UI::Control::ControlDisplay::MakeTransparent()
{
	IsOpaque_ = false;
	DisplayUpdateRequest();
}
void UI::Control::ControlDisplay::MakeOpaque()
{
	IsOpaque_ = true;
	DisplayUpdateRequest();
}

bool UI::Control::ControlDisplay::IsDisplay() const
{
	return IsOpaque() && IsVisible();
}
/*bool UI::Control::ControlDisplay::IsThisInteractible() const
{
	return IsEnabled() && IsDisplay();
}*/
bool UI::Control::ControlDisplay::IsInteractible() const
{
	return IsEnabled() && IsVisible();
}



/*unsigned int UI::Control::ControlDisplay::Layer() const
{
	return Layer_;
}*/
/*void UI::Control::ControlDisplay::LayerUpdate()
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
/*void UI::Control::ControlDisplay::LayerUpdateRecursive()
{
	LayerUpdate();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> LayerUpdateRecursive();
	}
}*/

/*float UI::Control::ControlDisplay::Depth() const
{
	return Depth_;
}*/
/*void UI::Control::ControlDisplay::DepthUpdate()
{
	if (Window == nullptr) { return; }
	if (Form == nullptr) { return; }

	float size = Window -> DepthSize;
	float offset = Form -> DepthOffset;
	float layer = Layer();

	Depth_ = -((layer * size) + offset);
}*/
/*void UI::Control::ControlDisplay::DepthUpdateRecursive()
{
	DepthUpdate();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> DepthUpdateRecursive();
	}
}*/
/*float UI::Control::ControlDisplay::Depth() const
{
	// return NaN ?
	if (Window == nullptr) { return 0.0f; }
	if (Form == nullptr) { return 0.0f; }
	return -((Layer() * (Window -> DepthSize)) + (Form -> DepthOffset));
}*/
float UI::Control::ControlDisplay::Depth(float diff) const
{
	if (_Window() == nullptr) { return 0.0f; }
	if (_Form() == nullptr) { return 0.0f; }
	return -(((Layer() + diff) * (_Window() -> DepthSize)) + (_Form() -> DepthOffset)); // put this Calculation in Form ?
}



void UI::Control::ControlDisplay::AnchorUpdateRequest()
{
	AnchorUpdateIsRequested = true;
}



/*void UI::Control::ControlDisplay::BoxUpdateRequest()
{
	BoxUpdateIsRequested = true;
}*/
/*void UI::Control::ControlDisplay::BoxUpdate()
{
	if (Parent == nullptr) { return; }

	Anchor.UpdateO(Parent -> BoxContent());

//	Anchor.UpdateO(Parent -> BoxContent);
//	BoxDisplay = Anchor.ToInnerBox(Parent -> BoxContent);
//
//	BoxBoarder.Min = BoxDisplay.Min + AnchorBoarder.Min;
//	BoxBoarder.Max = BoxDisplay.Max - AnchorBoarder.Max;
//
//	BoxContent.Min = BoxBoarder.Min + AnchorPadding.Min;
//	BoxContent.Max = BoxBoarder.Max - AnchorPadding.Max;

	BoxUpdateIsRequested = false;
}*/



void UI::Control::ControlDisplay::AutoAnchorUpdateRequest()
{
	AutoAnchorUpdateIsRequested = true;
}
void UI::Control::ControlDisplay::AutoAnchorUpdate()
{
	if (!IsVisible()) { return; }

	switch (AutoAnchorXType)
	{
		case EAutoAnchorType::None: break;
		default: break;
	}

	switch (AutoAnchorYType)
	{
		case EAutoAnchorType::None: break;
		case EAutoAnchorType::StackMin:		AutoAnchorUpdate_Y_StackMin(); break;
		//case EAutoAnchorType::StackMinFit:	AutoAnchorUpdate_Y_StackMinFit(); break;
		default: break;
	}

	AutoAnchorUpdateIsRequested = false;
}

/*void UI::Control::ControlDisplay::AutoAnchorUpdate_Y_StackMinFit()
{
	float y = 0.0f;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (Children[i] == nullptr) { continue; }
		Base & control = *Children[i];
		if (!control.IsVisible()) { continue; }
		control.Anchor.Y.AnchorMin(y);
		y = control.Anchor.Y.GetMinSize();
	}
	Anchor.Y.SetSize(y + AnchorMargin.Max.Y + AnchorBoarder.Max.Y + AnchorPadding.Max.Y);
	//BoxUpdateRequestRecursive();
	AnchorUpdateRequest();
}*/



/*void UI::Control::ControlDisplay::ColorUpdateRequest()
{
	ColorUpdateIsRequested = true;
}*/
/*void UI::Control::ControlDisplay::ColorUpdate()
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



void UI::Control::ControlDisplay::DisplayShow() { }
void UI::Control::ControlDisplay::DisplayHide() { }

void UI::Control::ControlDisplay::DisplayUpdateRequest()
{
	DisplayUpdateIsRequested = true;
}
void UI::Control::ControlDisplay::DisplayUpdate()
{
	if (IsDisplay())	{ DisplayShow(); }
	else				{ DisplayHide(); }

	DisplayUpdateIsRequested = false;
}


void UI::Control::ControlDisplay::Update()
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



UI::Control::ControlDisplay::ControlDisplay()
	: Anchor(
			AnchorSize,
			AnchorDist,
			AnchorMargin,
			AnchorBoarder,
			AnchorPadding,
			AnchorNormal
		)
{
	AnchorSize = VectorF2(0, 0);
	AnchorNormal = VectorF2(0, 0);
	AnchorDist = BoxF2(VectorF2(0, 0), VectorF2(0, 0));

	float margin = 2.5f;
	float boarder = 2.0f;
	float padding = 2.5f;

	AnchorMargin = BoxF2(VectorF2(margin, margin), VectorF2(margin, margin));
	AnchorBoarder = BoxF2(VectorF2(boarder, boarder), VectorF2(boarder, boarder));
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));
}



#include "User/MouseArgs.hpp"
#include "User/KeyBoardArgs.hpp"
#include "HoverArgs.hpp"
void UI::Control::ControlDisplay::RelayHover(HoverArgs args) { (void)args; }
void UI::Control::ControlDisplay::RelayClick(ClickArgs args) { (void)args; }
void UI::Control::ControlDisplay::RelayScroll(ScrollArgs args) { (void)args; }
void UI::Control::ControlDisplay::RelayDrag(DragArgs args) { (void)args; }
void UI::Control::ControlDisplay::RelayKey(KeyArgs args) { (void)args; }
void UI::Control::ControlDisplay::RelayText(TextArgs args) { (void)args; }
