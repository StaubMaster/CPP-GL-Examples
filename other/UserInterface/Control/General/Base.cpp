#include "Base.hpp"
#include "UIManager.hpp"

#include "User/MouseArgs.hpp"



HoverArgs::HoverArgs(HoverType type, DisplayPosition position)
	: Type(type)
	, Position(position)
{ }



void UI::Control::Base::ChangeManager(UI::Manager * manager)
{
	Manager = manager;
}

void UI::Control::Base::ChangeManagerRecursive(UI::Manager * manager)
{
	ChangeManager(manager);
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> ChangeManagerRecursive(manager);
	}
}



void UI::Control::Base::ChildInsert(Base & control)
{
	Children.Insert(&control);
	control.Parent = this;
	control.ChangeManagerRecursive(Manager);
	control.ObjectChangeRequest();
	control.BoxUpdateRequest();
	control.ColorUpdateRequest();
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
void UI::Control::Base::ChildClear()
{
	Children.Clear();
}

void UI::Control::Base::ChildInsert(Base * control)
{
	if (control != nullptr)
	{
		ChildInsert(*control);
	}
}
void UI::Control::Base::ChildRemove(Base * control)
{
	if (control != nullptr)
	{
		ChildRemove(*control);
	}
}

unsigned int UI::Control::Base::Layer() const
{
	if (Parent != nullptr)
	{
		return 1 + Parent -> Layer();
	}
	return 0;

	unsigned int layer = 0;
	const Base * control = this;
	while (control -> Parent != nullptr)
	{
		layer++;
		control = control -> Parent;
	}
	return layer;
}
unsigned int UI::Control::Base::LayerLimit() const
{
	if (Children.Count() != 0)
	{
		unsigned int limit = 0;
		for (unsigned int i = 0; i < Children.Count(); i++)
		{
			const Base * control = Children[i];
			if (control == nullptr) { continue; }
			unsigned int l = control -> LayerLimit();
			if (l > limit) { limit = l; }
		}
		return 1 + limit;
	}
	return 0;
}

void UI::Control::Base::AssignDepth(float offset, float size, unsigned int layer)
{
	Depth = 1.0f - ((layer * size) + offset);
	RelayAssignDepth();

	layer++;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Base * control = Children[i];
		if (control == nullptr) { continue; }
		control -> AssignDepth(offset, size, layer);
	}
}
void UI::Control::Base::RelayAssignDepth() { }



bool UI::Control::Base::IsEnabled() const
{
	return _Enabled;
}
void UI::Control::Base::MakeEnabled()
{
	_Enabled = true;
	ColorUpdateRequest();
}
void UI::Control::Base::MakeDisabled()
{
	_Enabled = false;
	ColorUpdateRequest();
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
	if (Parent == nullptr) { return; }

	BoxDisplay = Anchor.Calculate(Parent -> BoxContent);

	BoxBoarder.Min = BoxDisplay.Min + AnchorBoarder.Min;
	BoxBoarder.Max = BoxDisplay.Max - AnchorBoarder.Max;

	BoxContent.Min = BoxBoarder.Min + AnchorPadding.Min;
	BoxContent.Max = BoxBoarder.Max - AnchorPadding.Max;

	ObjectAssignBoxRequest();
}

void UI::Control::Base::BoxUpdateRequest()
{
	BoxUpdateIsRequested = true;

	// do this in BoxUpdate ?
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> BoxUpdateRequest();
	}
}
void UI::Control::Base::BoxUpdateResolve()
{
	if (BoxUpdateIsRequested)
	{
		BoxUpdate();
		BoxUpdateIsRequested = false;
	}
}
//void UI::Control::Base::BoxUpdateRequestRecursive()



void UI::Control::Base::UpdateAutoAnchor()
{
	switch (AutoAnchorXType)
	{
		case EAutoAnchorType::None: break;
		default: break;
	}

	switch (AutoAnchorYType)
	{
		case EAutoAnchorType::None: break;
		case EAutoAnchorType::StackMin:		UpdateAutoAnchor_Y_StackMin(); break;
		case EAutoAnchorType::StackMinFit:	UpdateAutoAnchor_Y_StackMinFit(); break;
		default: break;
	}

	if (Parent != nullptr)
	{
		Parent -> UpdateAutoAnchor();
	}
}
void UI::Control::Base::UpdateAutoAnchor_Y_StackMin()
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
void UI::Control::Base::UpdateAutoAnchor_Y_StackMinFit()
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



void UI::Control::Base::ColorUpdate()
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
	ObjectAssignColorRequest();
}

void UI::Control::Base::ColorUpdateRequest()
{
	ColorUpdateIsRequested = true;
}
void UI::Control::Base::ColorUpdateResolve()
{
	if (ColorUpdateIsRequested)
	{
		ColorUpdate();
		ColorUpdateIsRequested = false;
	}
}



void UI::Control::Base::Update()
{
	if (IsVisible())
	{
		BoxUpdateResolve();
	}
	ColorUpdateResolve();
}

void UI::Control::Base::RecursiveUpdate()
{
	Update();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> RecursiveUpdate();
	}
}



void UI::Control::Base::ObjectInsert()
{
	if (!Object.Is() && Manager != nullptr)
	{
		Object.Create();
		Object.Depth() = Depth;

		BoxUpdateIsRequested = true;
		ColorUpdateRequest();
	}
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
}

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
//void UI::Control::Base::ObjectChangeRequestRecursive()



void UI::Control::Base::ObjectAssignBox()
{
	Object.Box() = BoxDisplay;
	if (Parent != nullptr)
	{
		Object.Bound() = Parent -> BoxBoarder;
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
	Object.Color() = Color;
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



void UI::Control::Base::ObjectAssign()
{
	ObjectChangeResolve();
	if (Object.Is())
	{
		ObjectAssignBoxResolve();
		ObjectAssignColorResolve();
	}
}

void UI::Control::Base::RecursiveObjectAssign()
{
	ObjectAssign();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> RecursiveObjectAssign();
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

	float margin = 5;
	float boarder = 2;
	float padding = 5;

	AnchorMargin = BoxF2(VectorF2(margin, margin), VectorF2(margin, margin));
	AnchorBoarder = BoxF2(VectorF2(boarder, boarder), VectorF2(boarder, boarder));
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));
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
void UI::Control::Base::RelayDrag(DragArgs args) { (void)args; }
void UI::Control::Base::RelayKey(KeyArgs args) { (void)args; }
void UI::Control::Base::RelayText(TextArgs args) { (void)args; }
