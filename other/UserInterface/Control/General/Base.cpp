#include "Base.hpp"
#include "UIManager.hpp"

#include "User/MouseArgs.hpp"



void UI::Control::Base::ChangeManager(UI::Manager * manager)
{
	Manager = manager;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> ChangeManager(manager);
	}
}
void UI::Control::Base::ChangeManager(UI::Manager & manager)
{
	ChangeManager(&manager);
}

unsigned int UI::Control::Base::Layer() const
{
	unsigned int layer = 0;
	const Base * control = this;
	while (control -> Parent != nullptr)
	{
		layer++;
		control = control -> Parent;
	}
	return layer;
}

void UI::Control::Base::ChildInsert(Base & control)
{
	Children.Insert(&control);
	control.Parent = this;
	control.ChangeManager(Manager);
	control.ObjectChangeRequest();
	control.BoxUpdateRequest();
}
void UI::Control::Base::ChildInsert(Base * control)
{
	if (control != nullptr)
	{
		ChildInsert(*control);
	}
}

void UI::Control::Base::ChildRemove(Base & control)
{
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (Children[i] == &control)
		{
			Children.RemoveAt(i);
			i--;
		}
	}
}
void UI::Control::Base::ChildRemove(Base * control)
{
	if (control != nullptr)
	{
		ChildRemove(*control);
	}
}



bool UI::Control::Base::IsEnabled() const
{
	return _Enabled;
}
void UI::Control::Base::MakeEnabled()
{
	_Enabled = true;
	ObjectAssignColorRequest();
}
void UI::Control::Base::MakeDisabled()
{
	_Enabled = false;
	ObjectAssignColorRequest();
}

bool UI::Control::Base::IsThisVisible() const
{
	return _Visible;
}
void UI::Control::Base::Show()
{
	_Visible = true;
	ObjectChangeRequest();
}
void UI::Control::Base::Hide()
{
	_Visible = false;
	ObjectChangeRequest();
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
	ObjectChangeRequest();
}
void UI::Control::Base::MakeOpaque()
{
	_Opaque = true;
	ObjectChangeRequest();
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



void UI::Control::Base::BoxUpdate()
{
	if (Parent != nullptr)
	{
		BoxDisplay = Anchor.Calculate(Parent -> BoxContent);
		BoxContent.Min = BoxDisplay.Min + AnchorBoarder.Min + AnchorPadding.Min;
		BoxContent.Max = BoxDisplay.Max - AnchorBoarder.Max - AnchorPadding.Max;
		BoxUpdateIsRequested = false;
		ObjectAssignBoxRequest();
	}
	RelayBoxUpdate();
}

void UI::Control::Base::BoxUpdateRequest()
{
	BoxUpdateIsRequested = true;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> BoxUpdateRequest();
	}
	// do this in BoxUpdate ?
}
void UI::Control::Base::BoxUpdateResolve()
{
	if (BoxUpdateIsRequested)
	{
		BoxUpdate();
	}
}

void UI::Control::Base::RelayBoxUpdate() { }



void UI::Control::Base::UpdateAutoSize()
{
	switch (AutoSizerXType)
	{
		case EAutoSizerType::None: break;
		default: break;
	}

	switch (AutoSizerYType)
	{
		case EAutoSizerType::None: break;
		case EAutoSizerType::StackMin:		UpdateAutoSize_Y_StackMin(); break;
		case EAutoSizerType::StackMinFit:	UpdateAutoSize_Y_StackMinFit(); break;
		default: break;
	}

	if (Parent != nullptr)
	{
		Parent -> UpdateAutoSize();
	}
}
void UI::Control::Base::UpdateAutoSize_Y_StackMin()
{
	float y = 0.0f;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (Children[i] == nullptr) { continue; }
		Base & control = *Children[i];
		if (!control.IsVisible()) { continue; }
		control.Anchor.Y.AnchorMin(y);
		y = control.Anchor.Y.GetMinSize();
		control.BoxUpdateRequest();
	}
}
void UI::Control::Base::UpdateAutoSize_Y_StackMinFit()
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
	BoxUpdateRequest();
}



ColorF4 UI::Control::Base::ColorMake() const
{
	if (Manager -> Hovering != this)
	{
		return ColorDefault;
	}
	else
	{
		return ColorHover;
	}
}



void UI::Control::Base::Update()
{
	if (IsVisible())
	{
		BoxUpdateResolve();
	}

	RelayUpdate();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> Update();
	}
}

void UI::Control::Base::RelayUpdate() { }



void UI::Control::Base::ObjectChangeRequest()
{
	ObjectChangeIsRequested = true;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> ObjectChangeRequest();
	}
}
void UI::Control::Base::ObjectChangeResolve()
{
	if (ObjectChangeIsRequested)
	{
		if (IsDrawable())
		{
			ObjectInsert();
		}
		else
		{
			ObjectRemove();
		}
		ObjectChangeIsRequested = false;
	}
}

void UI::Control::Base::ObjectInsert()
{
	if (!Object.Is() && Manager != nullptr)
	{
		Object.Create();
		Object.Layer() = Depth;

		BoxUpdateRequest();
		ObjectAssignColorRequest();
	}
	RelayObjectInsert();
}
void UI::Control::Base::ObjectRemove()
{
	if (Object.Is() || Manager == nullptr)
	{
		if (Object.Is())
		{
			Object.Hide();
		}
		Object.Delete();
	}
	RelayObjectRemove();
}

void UI::Control::Base::RelayObjectInsert() { }
void UI::Control::Base::RelayObjectRemove() { }



void UI::Control::Base::ObjectAssignBox()
{
	Object.Box() = BoxDisplay;
	if (Parent != nullptr)
	{
		Object.Bound().Min = Parent -> BoxDisplay.Min + Parent -> AnchorBoarder.Min;
		Object.Bound().Max = Parent -> BoxDisplay.Max - Parent -> AnchorBoarder.Max;
	}
	else
	{
		Object.Bound() = BoxF2();
	}
}

void UI::Control::Base::ObjectAssignBoxRequest()
{
	ObjectAssignBoxIsRequested = true;
}
void UI::Control::Base::ObjectAssignBoxResolve()
{
	if (ObjectAssignBoxIsRequested)
	{
		ObjectAssignBox();
		ObjectAssignBoxIsRequested = false;
	}
}



void UI::Control::Base::ObjectAssignColor()
{
	Object.Color() = ColorMake();
}

void UI::Control::Base::ObjectAssignColorRequest()
{
	ObjectAssignColorIsRequested = true;
}
void UI::Control::Base::ObjectAssignColorResolve()
{
	if (ObjectAssignColorIsRequested)
	{
		ObjectAssignColor();
		ObjectAssignColorIsRequested = false;
	}
}



void UI::Control::Base::Assign()
{
	ObjectChangeResolve();

	if (Object.Is())
	{
		ObjectAssignBoxResolve();
		ObjectAssignColorResolve();
	}

	RelayAssign();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> Assign();
	}
}

void UI::Control::Base::RelayAssign() { }



UI::Control::Base::~Base()
{
	/*for (unsigned int i = 0; i < Children.Count(); i++)
	{
		delete Children[i];
	}*/
}
UI::Control::Base::Base()
	: Manager(nullptr)
	, Parent(nullptr)
	, Children()
	, Depth(0.0f)
	, _Enabled(true)
	, _Visible(true)
	, _Opaque(true)
	, Anchor(
			AnchorSize,
			AnchorDist,
			AnchorMargin,
			AnchorBoarder,
			AnchorPadding,
			AnchorNormal
		)
	, BoxDisplay()
	, BoxContent()
	, BoxUpdateIsRequested(false)
	, AutoSizerXType(EAutoSizerType::None)
	, AutoSizerYType(EAutoSizerType::None)
	, Object()
	, ObjectAssignBoxIsRequested(false)
	, ObjectAssignColorIsRequested(false)
{
	AnchorSize = VectorF2(0, 0);
	AnchorNormal = VectorF2(0, 0);
	AnchorDist = BoxF2(VectorF2(0, 0), VectorF2(0, 0));

	float margin = 5;
	float boarder = 2;
	float padding = 5;

	AnchorMargin = BoxF2(VectorF2(margin, margin), VectorF2(margin, margin));
	AnchorBoarder = BoxF2(VectorF2(boarder, boarder), VectorF2(boarder, boarder));
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));
}



void UI::Control::Base::ChangeAnchorBox(BoxF2 box, EBoxChangeType type)
{
	if (type == EBoxChangeType::None) { return; }
	if (Parent != nullptr)
	{
		// when moving, keep size
		// when resizing, keep other side

		BoxF2 other_box;
		other_box.Min = (Parent -> BoxContent.Min) + AnchorMargin.Min;
		other_box.Max = (Parent -> BoxContent.Max) - AnchorMargin.Max;

		Bool2 limit_min = box.Min <= other_box.Min;
		Bool2 limit_max = box.Max >= other_box.Max;

		AnchorType anchor_type_x = Anchor.X.Anchor;
		AnchorType anchor_type_y = Anchor.Y.Anchor;

		if (type != EBoxChangeType::Move)
		{
			if      ( limit_min.GetX() &&  limit_max.GetX()) { anchor_type_x = AnchorType::Both; box.Min.X = other_box.Min.X; box.Max.X = other_box.Max.X; }
			else if ( limit_min.GetX() && !limit_max.GetX()) { anchor_type_x = AnchorType::Min;  box.Min.X = other_box.Min.X;                              }
			else if (!limit_min.GetX() &&  limit_max.GetX()) { anchor_type_x = AnchorType::Max;  box.Max.X = other_box.Max.X;                              }

			if      ( limit_min.GetY() &&  limit_max.GetY()) { anchor_type_y = AnchorType::Both; box.Min.Y = other_box.Min.Y; box.Max.Y = other_box.Max.Y; }
			else if ( limit_min.GetY() && !limit_max.GetY()) { anchor_type_y = AnchorType::Min;  box.Min.Y = other_box.Min.Y;                              }
			else if (!limit_min.GetY() &&  limit_max.GetY()) { anchor_type_y = AnchorType::Max;  box.Max.Y = other_box.Max.Y;                              }
		}
		else
		{
			VectorF2 size = box.Max - box.Min;

			if      ( limit_min.GetX() &&  limit_max.GetX()) { anchor_type_x = AnchorType::Both; box.Min.X = other_box.Min.X; box.Max.X = other_box.Max.X;    }
			else if ( limit_min.GetX() && !limit_max.GetX()) { anchor_type_x = AnchorType::Min;  box.Min.X = other_box.Min.X; box.Max.X = box.Min.X + size.X; }
			else if (!limit_min.GetX() &&  limit_max.GetX()) { anchor_type_x = AnchorType::Max;  box.Max.X = other_box.Max.X; box.Min.X = box.Max.X - size.X; }

			if      ( limit_min.GetY() &&  limit_max.GetY()) { anchor_type_y = AnchorType::Both; box.Min.Y = other_box.Min.Y; box.Max.Y = other_box.Max.Y;    }
			else if ( limit_min.GetY() && !limit_max.GetY()) { anchor_type_y = AnchorType::Min;  box.Min.Y = other_box.Min.Y; box.Max.Y = box.Min.Y + size.Y; }
			else if (!limit_min.GetY() &&  limit_max.GetY()) { anchor_type_y = AnchorType::Max;  box.Max.Y = other_box.Max.Y; box.Min.Y = box.Max.Y - size.Y; }
		}

		Anchor.X.Anchor = anchor_type_x;
		Anchor.Y.Anchor = anchor_type_y;
		Anchor.Calculate(Parent -> BoxContent, box);
		BoxUpdateRequest();
	}
}



UI::Control::Base * UI::Control::Base::FindHover(const VectorF2 & mouse)
{
	if (!_Visible) { return nullptr; }
	if (!_Enabled) { return nullptr; }
	if (!BoxDisplay.Intersekt(mouse)) { return nullptr; }

	// check BoxContent before checking children ?
	Base * control = nullptr;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Base * c = Children[i] -> FindHover(mouse);
		if (c == nullptr) { continue; }
		if (control == nullptr || ((c -> Depth) < (control -> Depth)))
		{
			control = c;
		}
	}
	if (control != nullptr)
	{
		return control;
	}
	return this;
}

/*void UI::Control::Base::ChangeHover(HoverArgs args)
{
	if (args == HoverArgs::Enter)
	{
		if (IsEnabled() && Object.Is())
		{
			Object.Color() = ColorHover;
		}
	}
	if (args == HoverArgs::Leave)
	{
		if (IsEnabled() && Object.Is())
		{
			Object.Color() = ColorDefault;
		}
	}
}*/



void UI::Control::Base::RelayHover(HoverArgs args) { (void)args; }
void UI::Control::Base::RelayClick(ClickArgs args) { (void)args; }
void UI::Control::Base::RelayScroll(ScrollArgs args) { (void)args; }
void UI::Control::Base::RelayCursorDrag(DragArgs args) { (void)args; }
void UI::Control::Base::RelayKey(KeyArgs args) { (void)args; }
void UI::Control::Base::RelayText(TextArgs args) { (void)args; }
