#include "Base.hpp"
#include "Manager.hpp"
#include "UserParameter/MouseInclude.hpp"
#include <iostream>



UI::Control::Base::Base() :
	ControlManager(NULL),
	TextManager(NULL),
	ControlEntry(),
	Parent(NULL),
	Children(),
	Layer(0.0f),
	_Enabled(true),
	_Visible(true),
	_Opaque(true),
	_Drawable(true),
	_Interactible(true),
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
	/*for (unsigned int i = 0; i < Children.Count(); i++)
	{
		delete Children[i];
	}*/
}



void UI::Control::Base::ChildInsert(Base & control)
{
	std::cout << "Insert Child ....\n";
	Children.Insert(&control);
	control.Parent = this;
	control.ChangeManager(ControlManager);
	control.ChangeManager(TextManager);
	control.UpdateBox();
	control.UpdateDrawable();
	std::cout << "Insert Child done\n";
}
void UI::Control::Base::ChildInsert(Base * control)
{
	ChildInsert(*control);
}
void UI::Control::Base::ChangeManager(Manager * manager)
{
	ControlManager = manager;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> ChangeManager(manager);
	}
}
void UI::Control::Base::ChangeManager(UI::Text::Manager * manager)
{
	TextManager = manager;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> ChangeManager(manager);
	}
}





void UI::Control::Base::UpdateEntrys()
{
	if (ControlEntry.Is())
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



void UI::Control::Base::MakeEnabled()
{
	_Enabled = true;
	_Interactible = _Enabled && _Drawable;
	//UpdateDrawable();
}
void UI::Control::Base::MakeDisabled()
{
	_Enabled = false;
	_Interactible = _Enabled && _Drawable;
	//UpdateDrawable();
}

void UI::Control::Base::Show()
{
	_Visible = true;
	UpdateDrawable();
}
void UI::Control::Base::Hide()
{
	_Visible = false;
	UpdateDrawable();
}

void UI::Control::Base::MakeTransparent()
{
	_Opaque = false;
	//RemoveDrawingEntry();
	UpdateDrawable();
}
void UI::Control::Base::MakeOpaque()
{
	_Opaque = true;
	//InsertDrawingEntry();
	UpdateDrawable();
}

void UI::Control::Base::UpdateDrawable()
{
	if (Parent != NULL)
	{ _Drawable = _Visible && (Parent -> _Drawable); }
	else
	{ _Drawable = _Visible; }

	if (_Drawable && _Opaque)
	{ InsertDrawingEntry(); }
	else
	{ RemoveDrawingEntry(); }

	_Interactible = _Enabled && _Drawable;

	if (_Drawable)
	{ UpdateBox(); }

	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateDrawable();
	}
}
void UI::Control::Base::InsertDrawingEntry()
{
	if (!ControlEntry.Is() && ControlManager != NULL)
	{
		ControlEntry.Allocate(ControlManager -> Inst_Data_Container, 1);
		(*ControlEntry).Layer = Layer;
		AnchorBoxChanged = true;
		ColorChanged = true;
	}
	InsertDrawingEntryRelay();
}
void UI::Control::Base::RemoveDrawingEntry()
{
	if (ControlEntry.Is() || ControlManager == NULL)
	{
		ControlEntry.Dispose();
	}
	RemoveDrawingEntryRelay();
}



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



UI::Control::Base * UI::Control::Base::CheckHover(Point2D mouse)
{
	if (!_Visible) { return NULL; }
	if (!_Enabled) { return NULL; }
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



void UI::Control::Base::UpdateEntryAnchorBoxRelay()
{
	(*ControlEntry).Min = AnchorBox.Min;
	(*ControlEntry).Max = AnchorBox.Max;
	AnchorBoxChanged = false;
}
void UI::Control::Base::UpdateEntryColorRelay()
{
	if (ControlManager -> Hovering != this)
	{ (*ControlEntry).Col = ColorDefault; }
	else
	{ (*ControlEntry).Col = ColorHover; }
	ColorChanged = false;
}
void UI::Control::Base::UpdateEntrysRelay() { }

void UI::Control::Base::InsertDrawingEntryRelay() { }
void UI::Control::Base::RemoveDrawingEntryRelay() { }
void UI::Control::Base::UpdateBoxRelay() { }



void UI::Control::Base::RelayHover(unsigned char type)
{
	(void)type;
}
void UI::Control::Base::RelayClick(UserParameter::Mouse::Click params)
{
	(void)params;
}
void UI::Control::Base::RelayScroll(UserParameter::Mouse::Scroll params)
{
	(void)params;
}
void UI::Control::Base::RelayCursorDrag(UserParameter::Mouse::Drag params)
{
	(void)params;
}
void UI::Control::Base::RelayKey(UserParameter::KeyBoard::Key params)
{
	(void)params;
}
void UI::Control::Base::RelayText(UserParameter::KeyBoard::Text params)
{
	(void)params;
}
