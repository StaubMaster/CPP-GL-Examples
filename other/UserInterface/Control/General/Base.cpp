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
	control.DisplayChangeRequest();
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

// store (Layer) in (Base)
// store (LayerLimit) in (Form)
// store (*Form) in (Base)
// store (DepthOffset) in (Form)
// store (DepthSize) in (Manager)
void UI::Control::Base::AssignDepth(float offset, float size, unsigned int layer)
{
	Depth = -((layer * size) + offset);
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
	ColorUpdateRequestRecursive();
}
void UI::Control::Base::MakeDisabled()
{
	_Enabled = false;
	ColorUpdateRequestRecursive();
}

bool UI::Control::Base::IsThisVisible() const
{
	return _Visible;
}
void UI::Control::Base::Show()
{
	_Visible = true;
	DisplayChangeRequest();
}
void UI::Control::Base::Hide()
{
	_Visible = false;
	DisplayChangeRequest();
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
	DisplayChangeRequest();
}
void UI::Control::Base::MakeOpaque()
{
	_Opaque = true;
	DisplayChangeRequest();
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

void UI::Control::Base::BoxUpdateRequest()
{
	BoxUpdateIsRequested = true;
}



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
}

void UI::Control::Base::ColorUpdateResolve()
{
	if (ColorUpdateIsRequested)
	{
		ColorUpdate();
		ColorUpdateIsRequested = false;
	}
}

void UI::Control::Base::ColorUpdateRequest()
{
	ColorUpdateIsRequested = true;
}
void UI::Control::Base::ColorUpdateRequestRecursive()
{
	ColorUpdateRequest();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> ColorUpdateRequestRecursive();
	}
}



void UI::Control::Base::DisplayPut() const
{
	if (Manager != nullptr)
	{
		//Manager -> ControlManager.InstancePut(ObjectData);
		if (Display)
		{
			Inst::BufferData data;
			data.Layer = Depth;
			data.Box = BoxDisplay;
			data.Color = Color;
			if (Parent != nullptr)
			{
				data.Bound = Parent -> BoxBoarder;
			}
			else
			{
				data.Bound = BoxF2();
			}
			Manager -> ControlManager.InstancePut(data);
		}
	}
}

void UI::Control::Base::DisplayPutRecursive() const
{
	DisplayPut();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> DisplayPutRecursive();
	}
}

void UI::Control::Base::DisplayShow()
{
	Display = true;

	BoxUpdateIsRequested = true;
	ColorUpdateRequest();
}
void UI::Control::Base::DisplayHide()
{
	Display = false;
}

void UI::Control::Base::DisplayChangeRequest()
{
	DisplayChangeIsRequested = true;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> DisplayChangeRequest();
	}
}
void UI::Control::Base::DisplayChangeResolve()
{
	if (DisplayChangeIsRequested)
	{
		if (IsDrawable())
		{
			DisplayShow();
		}
		else
		{
			DisplayHide();
		}
		DisplayChangeIsRequested = false;
	}
}

void UI::Control::Base::DisplayChange()
{
	DisplayChangeResolve();
}



void UI::Control::Base::Update()
{
	BoxUpdateResolve();
	ColorUpdateResolve();
	DisplayChange();
}

void UI::Control::Base::UpdateRecursive()
{
	Update();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateRecursive();
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
