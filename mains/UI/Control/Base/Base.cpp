#include "Base.hpp"
#include "Manager.hpp"
#include <iostream>



UI::Control::Base::Base(Manager & manager) :
	ControlManager(manager),
	Entry(),
	Children()
{
	Visible = true;

	//AnchorDist = AxisBox2D(Point2D(12, 12), Point2D(12, 12));
	AnchorDist = AxisBox2D(Point2D(0, 0), Point2D(0, 0));

	//float padding = 10;
	//float padding = 5;
	float padding = 0;
	AnchorPadding = AxisBox2D(Point2D(padding, padding), Point2D(padding, padding));
	AnchorBoxChanged = false;

	ColorChanged = false;

	ClickFunc = NULL;
}
UI::Control::Base::~Base()
{
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		delete Children[i];
	}
}



void UI::Control::Base::ChildInsert(Base * control)
{
	Children.Insert(control);
	control -> UpdateBox(AnchorBox);
}
/*Point2D UI::Control::Base::PaddedSize()
{
	//return AnchorPadding.Min + AnchorSize + AnchorPadding.Max;
	return AnchorSize;
}*/



float	UI::Control::Base::GetPaddedMinX()
{
	if (Anchor.X.Anchor == ANCHOR_NONE) { return 0.0f; }
	if (Anchor.X.Anchor == ANCHOR_MIN)  { return AnchorDist.Min.X; }
	if (Anchor.X.Anchor == ANCHOR_MAX)  { return AnchorDist.Min.X + AnchorSize.X; }
	if (Anchor.X.Anchor == ANCHOR_BOTH) { return AnchorDist.Min.X; }
	return 0.0f;
}
float	UI::Control::Base::GetPaddedMaxX()
{
	if (Anchor.X.Anchor == ANCHOR_NONE) { return 0.0f; }
	if (Anchor.X.Anchor == ANCHOR_MIN)  { return AnchorDist.Max.X; }
	if (Anchor.X.Anchor == ANCHOR_MAX)  { return AnchorDist.Max.X + AnchorSize.X; }
	if (Anchor.X.Anchor == ANCHOR_BOTH) { return AnchorDist.Max.X; }
	return 0.0f;
}
float	UI::Control::Base::GetPaddedMinY()
{
	if (Anchor.Y.Anchor == ANCHOR_NONE) { return 0.0f; }
	if (Anchor.Y.Anchor == ANCHOR_MIN)  { return AnchorDist.Min.Y; }
	if (Anchor.Y.Anchor == ANCHOR_MAX)  { return AnchorDist.Min.Y + AnchorSize.Y; }
	if (Anchor.Y.Anchor == ANCHOR_BOTH) { return AnchorDist.Min.Y; }
	return 0.0f;
}
float	UI::Control::Base::GetPaddedMaxY()
{
	if (Anchor.Y.Anchor == ANCHOR_NONE) { return 0.0f; }
	if (Anchor.Y.Anchor == ANCHOR_MIN)  { return AnchorDist.Max.Y; }
	if (Anchor.Y.Anchor == ANCHOR_MAX)  { return AnchorDist.Max.Y + AnchorSize.Y; }
	if (Anchor.Y.Anchor == ANCHOR_BOTH) { return AnchorDist.Max.Y; }
	return 0.0f;
}

void	UI::Control::Base::SetPaddedMinX(float val)
{
	if (Anchor.X.Anchor == ANCHOR_NONE) { }
	if (Anchor.X.Anchor == ANCHOR_MIN)  { AnchorDist.Min.X = val; }
	if (Anchor.X.Anchor == ANCHOR_MAX)  { AnchorDist.Min.X = val - AnchorSize.X; }
	if (Anchor.X.Anchor == ANCHOR_BOTH) { AnchorDist.Min.X = val; }
}
void	UI::Control::Base::SetPaddedMaxX(float val)
{
	if (Anchor.X.Anchor == ANCHOR_NONE) { }
	if (Anchor.X.Anchor == ANCHOR_MIN)  { AnchorDist.Max.X = val; }
	if (Anchor.X.Anchor == ANCHOR_MAX)  { AnchorDist.Max.X = val - AnchorSize.X; }
	if (Anchor.X.Anchor == ANCHOR_BOTH) { AnchorDist.Max.X = val; }
}
void	UI::Control::Base::SetPaddedMinY(float val)
{
	if (Anchor.Y.Anchor == ANCHOR_NONE) { }
	if (Anchor.Y.Anchor == ANCHOR_MIN)  { AnchorDist.Min.Y = val; }
	if (Anchor.Y.Anchor == ANCHOR_MAX)  { AnchorDist.Min.Y = val - AnchorSize.Y; }
	if (Anchor.Y.Anchor == ANCHOR_BOTH) { AnchorDist.Min.Y = val; }
}
void	UI::Control::Base::SetPaddedMaxY(float val)
{
	if (Anchor.Y.Anchor == ANCHOR_NONE) { }
	if (Anchor.Y.Anchor == ANCHOR_MIN)  { AnchorDist.Max.Y = val; }
	if (Anchor.Y.Anchor == ANCHOR_MAX)  { AnchorDist.Max.Y = val - AnchorSize.Y; }
	if (Anchor.Y.Anchor == ANCHOR_BOTH) { AnchorDist.Max.Y = val; }
}



void UI::Control::Base::Info(std::string padding) const
{
	std::cout << padding << "this " << this << '\n';
	std::cout << padding << "Entry " << Entry.Is() << '\n';
	std::cout << padding << "Children " << Children.Count() << '\n';
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> Info(padding + "  ");
	}
}



void UI::Control::Base::UpdateEntrys()
{
	if (Entry.Is())
	{
		if (AnchorBoxChanged)
		{
			UpdateEntryAnchorBoxRelay();
			AnchorBoxChanged = false;
		}
		if (ColorChanged)
		{
			UpdateEntryColorRelay();
			ColorChanged = false;
		}
	}
	UpdateEntrysRelay();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateEntrys();
	}
}
void UI::Control::Base::UpdateEntryAnchorBoxRelay()
{
	(*Entry).Min = AnchorBox.Min;
	(*Entry).Max = AnchorBox.Max;
	AnchorBoxChanged = false;
}
void UI::Control::Base::UpdateEntryColorRelay()
{
	if (ControlManager.Hovering != this)
	{ (*Entry).Col = ColorDefault; }
	else
	{ (*Entry).Col = ColorHover; }
	ColorChanged = false;
}
void UI::Control::Base::UpdateEntrysRelay()
{

}



void UI::Control::Base::Show()
{
	Visible = true;
	UpdateVisibility(true);
}
void UI::Control::Base::Hide()
{
	Visible = false;
	UpdateVisibility(false);
}

void UI::Control::Base::UpdateVisibility(bool make_visible)
{
	if (make_visible)
	{
		if (Visible == true && !Entry.Is())
		{
			Entry.Allocate(ControlManager.Inst_Data_Container, 1);
			(*Entry).Layer = Layer;
			AnchorBoxChanged = true;
			ColorChanged = true;
		}
	}
	else
	{
		if (Entry.Is())
		{
			Entry.Dispose();
		}
	}
	UpdateVisibilityRelay(make_visible);
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateVisibility(make_visible);
	}
}
void UI::Control::Base::UpdateVisibilityRelay(bool make_visible)
{
	(void)make_visible;
}



void UI::Control::Base::UpdateBox(const AxisBox2D & BaseBox)
{
	AnchorBox = Anchor.Calculate(AnchorDist, AnchorSize, AnchorNormal, BaseBox);
	AnchorBox.Min += AnchorPadding.Min;
	AnchorBox.Max -= AnchorPadding.Max;
	AnchorBoxChanged = true;
	UpdateBoxRelay();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateBox(AnchorBox);
	}
}
void UI::Control::Base::UpdateBoxRelay()
{

}



UI::Control::Base * UI::Control::Base::CheckHover(Point2D mouse)
{
	if (!Visible) { return NULL; }
	if (AnchorBox.Intersekt(mouse))
	{
		Base * control = NULL;
		for (unsigned int i = 0; i < Children.Count(); i++)
		{
			Base * c = Children[i] -> CheckHover(mouse);
			if (c != NULL && (control == NULL || c -> Layer < control -> Layer))
			{
				control = c;
			}
		}
		if (control != NULL)
		{ return control; }
		return this;
	}
	return NULL;
}

void UI::Control::Base::HoverEnter()
{
	ColorChanged = true;
	RelayHover(1);
}
void UI::Control::Base::HoverLeave()
{
	ColorChanged = true;
	RelayHover(0);
}
void UI::Control::Base::RelayHover(unsigned char type)
{
	(void)type;
}


void UI::Control::Base::RelayClick(UI::Parameter::Click params)
{
	(void)params;
}
void UI::Control::Base::RelayKey(UI::Parameter::Key params)
{
	(void)params;
}
void UI::Control::Base::RelayText(UI::Parameter::Text params)
{
	(void)params;
}
