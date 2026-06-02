#include "Base.hpp"
#include "Manager.hpp"

#include "User/MouseArgs.hpp"



unsigned char UI::Control::Base::Layer() const
{
	unsigned char layer = 0;
	const Base * control = this;
	while (control -> Parent != nullptr)
	{
		layer++;
		control = control -> Parent;
	}
	return layer;
}

bool UI::Control::Base::IsEnabled() const
{
	return _Enabled;
}
void UI::Control::Base::MakeEnabled()
{
	_Enabled = true;
	ObjectColorNeedAssign = true;
}
void UI::Control::Base::MakeDisabled()
{
	_Enabled = false;
	ObjectColorNeedAssign = true;
}

bool UI::Control::Base::IsThisVisible() const
{
	return _Visible;
}
void UI::Control::Base::Show()
{
	_Visible = true;
	DrawableWantUpdate();
}
void UI::Control::Base::Hide()
{
	_Visible = false;
	DrawableWantUpdate();
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
	DrawableWantUpdate();
}
void UI::Control::Base::MakeOpaque()
{
	_Opaque = true;
	DrawableWantUpdate();
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
bool UI::Control::Base::IsThisInteractible() const
{
	return _Enabled && IsDrawable();
}
bool UI::Control::Base::IsInteractible() const
{
	return _Enabled && IsVisible();
}



void UI::Control::Base::DrawableWantUpdate()
{
	DrawableNeedUpdate = true;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> DrawableWantUpdate();
	}
}
void UI::Control::Base::BoxWantUpdate()
{
	BoxNeedUpdate = true;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> BoxWantUpdate();
	}
}



UI::Control::Base::~Base()
{
	/*for (unsigned int i = 0; i < Children.Count(); i++)
	{
		delete Children[i];
	}*/
}
UI::Control::Base::Base()
	: ControlManager(nullptr)
	, TextManager(nullptr)
	, ControlObject()
	, Parent(nullptr)
	, Children()
	, Depth(0.0f)
	, _Enabled(true)
	, _Visible(true)
	, _Opaque(true)
	, Anchor(
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
	float boarder = 5;
	float padding = 5;

	AnchorMargin = BoxF2(VectorF2(margin, margin), VectorF2(margin, margin));
	AnchorBoarder = BoxF2(VectorF2(boarder, boarder), VectorF2(boarder, boarder));
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));
}



void UI::Control::Base::ChildInsert(Base & control)
{
	Children.Insert(&control);
	control.Parent = this;
	control.ChangeManager(ControlManager);
	control.ChangeManager(TextManager);
	control.DrawableWantUpdate();
	control.BoxWantUpdate();
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





void UI::Control::Base::Update()
{
	if (DrawableNeedUpdate)
	{
		if (IsDrawable())
		{ InsertObject(); }
		else
		{ RemoveObject(); }
		DrawableNeedUpdate = false;
	}

	if (IsVisible())
	{
		if (BoxNeedUpdate)
		{
			UpdateBox();
			BoxNeedUpdate = false;
		}
	}

	if (ControlObject.Is())
	{
		if (ObjectBoxNeedAssign)
		{
			AssignObjectBox();
			ObjectBoxNeedAssign = false;
		}
		if (ObjectColorNeedAssign)
		{
			AssignObjectColor();
			ObjectColorNeedAssign = false;
		}
	}

	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> Update();
	}
}

void UI::Control::Base::ChangeAnchorBox(BoxF2 box)
{
	if (Parent != nullptr)
	{
		// limit based on Parent ContainerBox
		// use Margin of Parent and Padding of this

		Anchor.Calculate(Parent -> ContainerBox, box);
		BoxWantUpdate();
	}
}

void UI::Control::Base::UpdateBox()
{
	if (Parent != nullptr)
	{
		DisplayBox = Anchor.Calculate(Parent -> ContainerBox);
		ContainerBox.Min = DisplayBox.Min + AnchorBoarder.Min + AnchorPadding.Min;
		ContainerBox.Max = DisplayBox.Max - AnchorBoarder.Max - AnchorPadding.Max;
		ObjectBoxNeedAssign = true;
	}
	RelayUpdateBox();
}
void UI::Control::Base::InsertObject()
{
	if (!ControlObject.Is() && ControlManager != nullptr)
	{
		ControlObject.Create();
		ControlObject.Layer() = Depth;

		BoxNeedUpdate = true;
		ObjectBoxNeedAssign = true;
		ObjectColorNeedAssign = true;
	}
	RelayInsertObject();
}
void UI::Control::Base::RemoveObject()
{
	if (ControlObject.Is() || ControlManager == nullptr)
	{
		if (ControlObject.Is())
		{
			ControlObject.Hide();
		}
		ControlObject.Delete();
	}
	RelayRemoveObject();
}
void UI::Control::Base::AssignObjectBox()
{
	ControlObject.Box() = DisplayBox;
	RelayAssignObjectBox();
}
void UI::Control::Base::AssignObjectColor()
{
	if (ControlManager -> Hovering != this)
	{
		ControlObject.Color() = ColorDefault;
	}
	else
	{
		ControlObject.Color() = ColorHover;
	}
	RelayAssignObjectColor();
}

void UI::Control::Base::RelayUpdateBox() { }
void UI::Control::Base::RelayInsertObject() { }
void UI::Control::Base::RelayRemoveObject() { }
void UI::Control::Base::RelayAssignObjectBox() { }
void UI::Control::Base::RelayAssignObjectColor() { }



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
			if (c != nullptr && (control == nullptr || c -> Depth < control -> Depth))
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



void UI::Control::Base::RelayHover(unsigned char type) { (void)type; }
void UI::Control::Base::RelayClick(ClickArgs args) { (void)args; }
void UI::Control::Base::RelayScroll(ScrollArgs args) { (void)args; }
void UI::Control::Base::RelayCursorDrag(DragArgs args) { (void)args; }
void UI::Control::Base::RelayKey(KeyArgs args) { (void)args; }
void UI::Control::Base::RelayText(TextArgs args) { (void)args; }
