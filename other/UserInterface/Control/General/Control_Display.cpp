#include "Control_Display.hpp"
#include "Control/Form.hpp"
#include "UIManager.hpp"
#include "Control/Graphics/Inst/Data.hpp"



bool UI::Control::Control_Display::IsEnabled() const
{
	return IsEnabled_;
}
void UI::Control::Control_Display::Enable()
{
	IsEnabled_ = true;
	//ColorUpdateRequestRecursive();
}
void UI::Control::Control_Display::Disable()
{
	IsEnabled_ = false;
	//ColorUpdateRequestRecursive();
}

bool UI::Control::Control_Display::IsOpaque() const
{
	return IsOpaque_;
}
void UI::Control::Control_Display::MakeTransparent()
{
	IsOpaque_ = false;
	DisplayUpdateRequest();
}
void UI::Control::Control_Display::MakeOpaque()
{
	IsOpaque_ = true;
	DisplayUpdateRequest();
}

bool UI::Control::Control_Display::IsThisVisible() const
{
	return IsVisible_;
}
bool UI::Control::Control_Display::IsVisible() const
{
	return IsThisVisible();
}
void UI::Control::Control_Display::Show()
{
	IsVisible_ = true;
	DisplayUpdateRequest();
}
void UI::Control::Control_Display::Hide()
{
	IsVisible_ = false;
	DisplayUpdateRequest();
}

bool UI::Control::Control_Display::IsDisplay() const
{
	return IsOpaque() && IsVisible();
}
/*bool UI::Control::Control_Display::IsThisInteractible() const
{
	return IsEnabled() && IsDisplay();
}*/
bool UI::Control::Control_Display::IsInteractible() const
{
	return IsEnabled() && IsVisible();
}



/*unsigned int UI::Control::Control_Display::Layer() const
{
	return Layer_;
}*/
/*void UI::Control::Control_Display::LayerUpdate()
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
/*void UI::Control::Control_Display::LayerUpdateRecursive()
{
	LayerUpdate();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> LayerUpdateRecursive();
	}
}*/

/*float UI::Control::Control_Display::Depth() const
{
	return Depth_;
}*/
/*void UI::Control::Control_Display::DepthUpdate()
{
	if (Window == nullptr) { return; }
	if (Form == nullptr) { return; }

	float size = Window -> DepthSize;
	float offset = Form -> DepthOffset;
	float layer = Layer();

	Depth_ = -((layer * size) + offset);
}*/
/*void UI::Control::Control_Display::DepthUpdateRecursive()
{
	DepthUpdate();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> DepthUpdateRecursive();
	}
}*/
/*float UI::Control::Control_Display::Depth() const
{
	// return NaN ?
	if (Window == nullptr) { return 0.0f; }
	if (Form == nullptr) { return 0.0f; }
	return -((Layer() * (Window -> DepthSize)) + (Form -> DepthOffset));
}*/
/*float UI::Control::Control_Display::Depth(float diff) const
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



void UI::Control::Control_Display::AnchorUpdateRequest()
{
	AnchorUpdateIsRequested = true;
}
void UI::Control::Control_Display::AnchorUpdate()
{
	if (!MetaIs()) { return; }
	Anchor.UpdateO(MetaBoxContent());
	AnchorUpdateIsRequested = false;
}



/*void UI::Control::Control_Display::BoxUpdateRequest()
{
	BoxUpdateIsRequested = true;
}*/
/*void UI::Control::Control_Display::BoxUpdate()
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

BoxF2 UI::Control::Control_Display::BoxDisplay() const
{
	if (!MetaIs()) { return BoxF2(); }
	return Anchor.ToInnerBox(MetaBoxContent());
}
BoxF2 UI::Control::Control_Display::BoxBoarder() const
{
	if (!MetaIs()) { return BoxF2(); }
	BoxF2 box = BoxDisplay();
	return BoxF2(
		box.Min + AnchorBoarder.Min,
		box.Max - AnchorBoarder.Max
	);
}
BoxF2 UI::Control::Control_Display::BoxContent() const
{
	if (!MetaIs()) { return BoxF2(); }
	BoxF2 box = BoxBoarder();
	return BoxF2(
		box.Min + AnchorPadding.Min,
		box.Max - AnchorPadding.Max
	);
}



void UI::Control::Control_Display::AutoAnchorUpdateRequest()
{
	AutoAnchorUpdateIsRequested = true;
}
void UI::Control::Control_Display::AutoAnchorUpdate()
{
	if (!IsVisible()) { return; } // why is this check here ?

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



/*void UI::Control::Control_Display::ColorUpdateRequest()
{
	ColorUpdateIsRequested = true;
}*/
/*void UI::Control::Control_Display::ColorUpdate()
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



void UI::Control::Control_Display::DisplayUpdateRequest()
{
	DisplayUpdateIsRequested = true;
}
void UI::Control::Control_Display::DisplayUpdate()
{
	if (IsDisplay())	{ RelayShow(); }
	else				{ RelayHide(); }

	DisplayUpdateIsRequested = false;
}

void UI::Control::Control_Display::RelayShow() { }
void UI::Control::Control_Display::RelayHide() { }



void UI::Control::Control_Display::Update()
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



UI::Control::Control_Display::Control_Display()
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
