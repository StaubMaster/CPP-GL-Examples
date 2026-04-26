#include "Base.hpp"
#include "Manager.hpp"

#include "User/MouseArgs.hpp"



bool UI::Control::Base::IsEnabled() const
{
	return _Enabled;
}
void UI::Control::Base::MakeEnabled()
{
	_Enabled = true;
	//UpdateDrawable();
}
void UI::Control::Base::MakeDisabled()
{
	_Enabled = false;
	//UpdateDrawable();
}

bool UI::Control::Base::IsVisible() const
{
	return _Visible;
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

bool UI::Control::Base::IsTransparent() const
{
	return !_Opaque;
}
bool UI::Control::Base::IsOpaque() const
{
	return _Opaque;
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

// this loops over all Parents.
// cant imagine there being more then 10 Layers for the UI
// and it only does a simple check
// so this should be fine
bool UI::Control::Base::Drawable() const
{
	if (Parent != nullptr)
	{
		return _Visible && (Parent -> Drawable());
	}
	else
	{
		return _Visible;
	}
}
bool UI::Control::Base::Interactible() const
{
	return _Enabled && Drawable();
}



UI::Control::Base::Base() :
	ControlManager(nullptr),
	TextManager(nullptr),
	ControlObject(),
	Parent(nullptr),
	Children(),
	Layer(0.0f),
	_Enabled(true),
	_Visible(true),
	_Opaque(true),
	Anchor(
		Anchor1D(AnchorSize.X, AnchorNormal.X
			, AnchorDist.Min.X, AnchorDist.Max.X
			, AnchorPadding.Min.X, AnchorPadding.Max.X
		),
		Anchor1D(AnchorSize.Y, AnchorNormal.Y
			, AnchorDist.Min.Y, AnchorDist.Max.Y
			, AnchorPadding.Min.Y, AnchorPadding.Max.Y
		)
	)
{
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
	Children.Insert(&control);
	control.Parent = this;
	control.ChangeManager(ControlManager);
	control.ChangeManager(TextManager);
	control.UpdateBox();
	control.UpdateDrawable();
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
	if (ControlObject.Is())
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



void UI::Control::Base::UpdateDrawable()
{
	if (Drawable() && _Opaque)
	{ InsertDrawingEntry(); }
	else
	{ RemoveDrawingEntry(); }

	if (Drawable())
	{ UpdateBox(); }

	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateDrawable();
	}
}
void UI::Control::Base::InsertDrawingEntry()
{
	if (!ControlObject.Is() && ControlManager != nullptr)
	{
		ControlObject.Create();
		ControlObject.Layer() = Layer;
		AnchorBoxChanged = true;
		ColorChanged = true;
	}
	InsertDrawingEntryRelay();
}
void UI::Control::Base::RemoveDrawingEntry()
{
	if (ControlObject.Is() || ControlManager == nullptr)
	{
		ControlObject.Delete();
	}
	RemoveDrawingEntryRelay();
}



void UI::Control::Base::UpdateBox()
{
	if (Parent != nullptr)
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
	if (!_Visible) { return nullptr; }
	if (!_Enabled) { return nullptr; }
	if (AnchorBox.Intersekt(mouse))
	{
		Base * control = nullptr;
		for (unsigned int i = 0; i < Children.Count(); i++)
		{
			Base * c = Children[i] -> CheckHover(mouse);
			if (c != nullptr && (control == nullptr || c -> Layer < control -> Layer))
			{
				control = c;
			}
		}
		if (control != nullptr)
		{ return control; }
		return this;
	}
	return nullptr;
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
	ControlObject.Box() = AnchorBox;
	AnchorBoxChanged = false;
}
void UI::Control::Base::UpdateEntryColorRelay()
{
	if (ControlManager -> Hovering != this)
	{ ControlObject.Color() = ColorDefault; }
	else
	{ ControlObject.Color() = ColorHover; }
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
void UI::Control::Base::RelayClick(ClickArgs params)
{
	(void)params;
}
void UI::Control::Base::RelayScroll(ScrollArgs params)
{
	(void)params;
}
void UI::Control::Base::RelayCursorDrag(DragArgs params)
{
	(void)params;
}
void UI::Control::Base::RelayKey(KeyArgs params)
{
	(void)params;
}
void UI::Control::Base::RelayText(TextArgs params)
{
	(void)params;
}
