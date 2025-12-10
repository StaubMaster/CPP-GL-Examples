#include "Base.hpp"
#include "Manager.hpp"
#include <iostream>



UI::Control::Base::Base(Manager & manager) :
	ControlManager(manager),
	Entry(),
	Parent(NULL),
	Children(),
	Layer(0.0f),
	Anchor(
		Anchor1D(
			AnchorSize.X, AnchorDist.Min.X, AnchorDist.Max.X, AnchorNormal.X,
			AnchorPadding.Min.X, AnchorPadding.Max.X
		),
		Anchor1D(
			AnchorSize.Y, AnchorDist.Min.Y, AnchorDist.Max.Y, AnchorNormal.Y,
			AnchorPadding.Min.Y, AnchorPadding.Max.Y
		)
	)
{
	Enabled = true;
	Visible = true;
	Opaque = true;
	Drawable = true;

	//AnchorDist = AxisBox2D(Point2D(12, 12), Point2D(12, 12));
	AnchorDist = AxisBox2D(Point2D(0, 0), Point2D(0, 0));

	//float padding = 10;
	float padding = 5;
	//float padding = 0;
	AnchorPadding = AxisBox2D(Point2D(padding, padding), Point2D(padding, padding));
	AnchorBoxChanged = false;

	ColorChanged = false;
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
	control -> Parent = this;
	control -> UpdateBox();
	control -> UpdateVisibility();
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
void UI::Control::Base::UpdateEntrysRelay() { }



void UI::Control::Base::MakeEnabled()
{
	Enabled = true;
}
void UI::Control::Base::MakeDisabled()
{
	Enabled = false;
}

void UI::Control::Base::Show()
{
	Visible = true;
	UpdateVisibility();
}
void UI::Control::Base::Hide()
{
	Visible = false;
	UpdateVisibility();
}

void UI::Control::Base::MakeTransParent()
{
	Opaque = false;
	RemoveDrawingEntry();
	UpdateVisibility();
}
void UI::Control::Base::MakeOpaque()
{
	Opaque = true;
	InsertDrawingEntry();
	UpdateVisibility();
}

void UI::Control::Base::UpdateVisibility()
{
	if (Parent != NULL)
	{ Drawable = Visible && (Parent -> Drawable); }
	else
	{ Drawable = Visible; }

	if (Drawable && Opaque)
	{ InsertDrawingEntry(); }
	else
	{ RemoveDrawingEntry(); }

	if (Drawable)
	{ UpdateBox(); }

	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateVisibility();
	}
}
void UI::Control::Base::InsertDrawingEntry()
{
	if (!Entry.Is())
	{
		Entry.Allocate(ControlManager.Inst_Data_Container, 1);
		(*Entry).Layer = Layer;
		AnchorBoxChanged = true;
		ColorChanged = true;
	}
	InsertDrawingEntryRelay();
}
void UI::Control::Base::RemoveDrawingEntry()
{
	if (Entry.Is())
	{
		Entry.Dispose();
	}
	RemoveDrawingEntryRelay();
}
void UI::Control::Base::InsertDrawingEntryRelay() { }
void UI::Control::Base::RemoveDrawingEntryRelay() { }



void UI::Control::Base::UpdateBox()
{
	if (Parent != NULL)
	{
		AnchorBox = Anchor.Calculate(Parent -> AnchorBox);
		AnchorBoxChanged = true;
	}
	UpdateBoxRelay();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateBox();
	}
}
void UI::Control::Base::UpdateBoxRelay() { }



UI::Control::Base * UI::Control::Base::CheckHover(Point2D mouse)
{
	if (!Visible) { return NULL; }
	if (!Enabled) { return NULL; }
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



void UI::Control::Base::RelayClick(UserParameter::Click params)
{
	(void)params;
}
void UI::Control::Base::RelayScroll(UserParameter::Scroll params)
{
	(void)params;
}
void UI::Control::Base::RelayKey(UserParameter::Key params)
{
	(void)params;
}
void UI::Control::Base::RelayText(UserParameter::Text params)
{
	(void)params;
}
