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

bool UI::Control::Base::IsThisVisible() const
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

bool UI::Control::Base::IsVisible() const
{
	if (Parent != nullptr)
	{
		return _Visible && (Parent -> IsVisible());
	}
	else
	{
		return _Visible;
	}
}
bool UI::Control::Base::IsDrawable() const
{
	return _Opaque && IsVisible();
}
bool UI::Control::Base::IsInteractible() const
{
	return _Enabled && IsDrawable();
}



UI::Control::Base::~Base()
{
	/*for (unsigned int i = 0; i < Children.Count(); i++)
	{
		delete Children[i];
	}*/
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
			, AnchorMargin.Min.X, AnchorMargin.Max.X
			, AnchorBoarder.Min.X, AnchorBoarder.Max.X
			, AnchorPadding.Min.X, AnchorPadding.Max.X
		),
		Anchor1D(AnchorSize.Y, AnchorNormal.Y
			, AnchorDist.Min.Y, AnchorDist.Max.Y
			, AnchorMargin.Min.Y, AnchorMargin.Max.Y
			, AnchorBoarder.Min.Y, AnchorBoarder.Max.Y
			, AnchorPadding.Min.Y, AnchorPadding.Max.Y
		)
	)
{
	AnchorDist = BoxF2(VectorF2(0, 0), VectorF2(0, 0));

	float margin = 5;
	float boarder = 2;
	float padding = 5;

	AnchorMargin = BoxF2(VectorF2(margin, margin), VectorF2(margin, margin));
	AnchorBoarder = BoxF2(VectorF2(boarder, boarder), VectorF2(boarder, boarder));
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));

	//AnchorBoxChanged = false;

	//ColorChanged = false;
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





/*void UI::Control::Base::UpdateEntrys()
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
}*/



void UI::Control::Base::UpdateDrawable()
{
	if (IsDrawable())
	{ InsertDrawingEntry(); }
	else
	{ RemoveDrawingEntry(); }

	if (IsVisible())
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
		ControlObject.Box() = DisplayBox;
		ControlObject.Color() = ColorDefault;

		//if (ControlManager -> Hovering != this)
		//{ ControlObject.Color() = ColorDefault; }
		//else
		//{ ControlObject.Color() = ColorHover; }
	}
	InsertDrawingEntryRelay();
}
void UI::Control::Base::RemoveDrawingEntry()
{
	if (ControlObject.Is() || ControlManager == nullptr)
	{
		if (ControlObject.Is())
		{
			ControlObject.Hide(); // should Check if it Exists ?
		}
		ControlObject.Delete();
	}
	RemoveDrawingEntryRelay();
}



void UI::Control::Base::UpdateBox()
{
	if (Parent != nullptr && IsVisible())
	{
		DisplayBox = Anchor.Calculate(Parent -> ContainerBox);
		ContainerBox.Min = DisplayBox.Min + AnchorBoarder.Min + AnchorPadding.Min;
		ContainerBox.Max = DisplayBox.Max - AnchorBoarder.Max - AnchorPadding.Max;
		if (ControlObject.Is() && IsDrawable())
		{
			ControlObject.Box() = DisplayBox;
		}
	}
	UpdateBoxRelay();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateBox();
	}
}



UI::Control::Base * UI::Control::Base::CheckHover(VectorF2 mouse)
{
	if (!_Visible) { return nullptr; }
	if (!_Enabled) { return nullptr; }
	if (DisplayBox.Intersekt(mouse))
	{
		// check ContainerBox before checking children ?
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
	if (IsEnabled() && ControlObject.Is())
	{
		ControlObject.Color() = ColorHover;
	}
	RelayHover(1);
}
void UI::Control::Base::HoverLeave()
{
	if (IsEnabled() && ControlObject.Is())
	{
		ControlObject.Color() = ColorDefault;
	}
	RelayHover(0);
}



/*void UI::Control::Base::UpdateEntryAnchorBoxRelay()
{
	//ControlObject.Box() = AnchorBox;
	ControlObject.Box() = DisplayBox;
	AnchorBoxChanged = false;
}*/
/*void UI::Control::Base::UpdateEntryColorRelay()
{
	if (ControlManager -> Hovering != this)
	{ ControlObject.Color() = ColorDefault; }
	else
	{ ControlObject.Color() = ColorHover; }
	ColorChanged = false;
}*/
//void UI::Control::Base::UpdateEntrysRelay() { }

void UI::Control::Base::InsertDrawingEntryRelay() { }
void UI::Control::Base::RemoveDrawingEntryRelay() { }
void UI::Control::Base::UpdateBoxRelay() { }



void UI::Control::Base::RelayHover(unsigned char type) { (void)type; }
void UI::Control::Base::RelayClick(ClickArgs args) { (void)args; }
void UI::Control::Base::RelayScroll(ScrollArgs args) { (void)args; }
void UI::Control::Base::RelayCursorDrag(DragArgs args) { (void)args; }
void UI::Control::Base::RelayKey(KeyArgs args) { (void)args; }
void UI::Control::Base::RelayText(TextArgs args) { (void)args; }
