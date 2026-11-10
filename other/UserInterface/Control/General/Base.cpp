#include "Base.hpp"
#include "Control/Form.hpp"
#include "UIManager.hpp"
#include "Graphics/Inst/Data.hpp"



void UI::Control::Base::AssignPointers(Base & control)
{
	control.Parent = this;
	control.AssignPointerRecursive(Manager);
	control.AssignPointerRecursive(Window);
	control.AssignPointerRecursive(Form);
}

void UI::Control::Base::AssignPointer(UI::Manager * manager)
{
	Manager = manager;
}
void UI::Control::Base::AssignPointer(UI::Control::Window * window)
{
	Window = window;
}
void UI::Control::Base::AssignPointer(UI::Control::Form * form)
{
	Form = form;
}

void UI::Control::Base::AssignPointerRecursive(UI::Manager * manager)
{
	AssignPointer(manager);
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> AssignPointerRecursive(manager);
	}
}
void UI::Control::Base::AssignPointerRecursive(UI::Control::Window * window)
{
	AssignPointer(window);
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> AssignPointerRecursive(window);
	}
}
void UI::Control::Base::AssignPointerRecursive(UI::Control::Form * form)
{
	AssignPointer(form);
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> AssignPointerRecursive(form);
	}
}



void UI::Control::Base::ChildClear()
{
	Children.Clear();
	AutoAnchorUpdateRequest();
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
	AutoAnchorUpdateRequest();
}
void UI::Control::Base::ChildInsert(Base & control)
{
	AssignPointers(control);
	Children.Insert(&control);
	control.DisplayUpdateRequestRecursive();
	control.BoxUpdateRequestRecursive();
	control.ColorUpdateRequestRecursive();
	AutoAnchorUpdateRequest();
}

void UI::Control::Base::ChildRemove(Base * control)
{
	if (control != nullptr)
	{
		ChildRemove(*control);
	}
}
void UI::Control::Base::ChildInsert(Base * control)
{
	if (control != nullptr)
	{
		ChildInsert(*control);
	}
}



/*unsigned int UI::Control::Base::Layer() const
{
	return Layer_;
}*/
/*void UI::Control::Base::LayerUpdate()
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
/*void UI::Control::Base::LayerUpdateRecursive()
{
	LayerUpdate();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> LayerUpdateRecursive();
	}
}*/
unsigned int UI::Control::Base::Layer() const
{
	if (Parent != nullptr)
	{
		return (Parent -> Layer()) + 1;
	}
	else
	{
		return 0;
	}
}

unsigned int UI::Control::Base::LayerLimit() const
{
	if (Children.Count() != 0)
	{
		unsigned int limit = 0;
		for (unsigned int i = 0; i < Children.Count(); i++)
		{
			unsigned int l = Children[i] -> LayerLimit();
			if (l > limit) { limit = l; }
		}
		return limit + 1;
	}
	return 0;
}

/*float UI::Control::Base::Depth() const
{
	return Depth_;
}*/
/*void UI::Control::Base::DepthUpdate()
{
	if (Window == nullptr) { return; }
	if (Form == nullptr) { return; }

	float size = Window -> DepthSize;
	float offset = Form -> DepthOffset;
	float layer = Layer();

	Depth_ = -((layer * size) + offset);
}*/
/*void UI::Control::Base::DepthUpdateRecursive()
{
	DepthUpdate();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> DepthUpdateRecursive();
	}
}*/
float UI::Control::Base::Depth() const
{
	// return NaN ?
	if (Window == nullptr) { return 0.0f; }
	if (Form == nullptr) { return 0.0f; }

	const float & size = Window -> DepthSize;
	const float & offset = Form -> DepthOffset;
	float layer = Layer();

	return -((layer * size) + offset);
}



bool UI::Control::Base::IsEnabled() const
{
	return IsEnabled_;
}
void UI::Control::Base::Enable()
{
	IsEnabled_ = true;
	ColorUpdateRequestRecursive();
}
void UI::Control::Base::Disable()
{
	IsEnabled_ = false;
	ColorUpdateRequestRecursive();
}

bool UI::Control::Base::IsThisVisible() const
{
	return IsVisible_;
}
void UI::Control::Base::Show()
{
	IsVisible_ = true;
	DisplayUpdateRequestRecursive();
	if (Parent != nullptr)
	{
		Parent -> AutoAnchorUpdateRequest();
	}
}
void UI::Control::Base::Hide()
{
	IsVisible_ = false;
	DisplayUpdateRequestRecursive();
	if (Parent != nullptr)
	{
		Parent -> AutoAnchorUpdateRequest();
	}
}

bool UI::Control::Base::IsOpaque() const
{
	return IsOpaque_;
}
void UI::Control::Base::MakeTransparent()
{
	IsOpaque_ = false;
	DisplayUpdateRequest();
}
void UI::Control::Base::MakeOpaque()
{
	IsOpaque_ = true;
	DisplayUpdateRequest();
}

bool UI::Control::Base::IsVisible() const
{
	if (Parent != nullptr)
	{
		return IsThisVisible() && (Parent -> IsVisible());
	}
	else
	{
		return IsThisVisible();
	}
}
bool UI::Control::Base::IsDrawable() const
{
	return IsOpaque() && IsVisible();
}
bool UI::Control::Base::IsThisInteractible() const
{
	return IsEnabled() && IsDrawable();
}
bool UI::Control::Base::IsInteractible() const
{
	return IsEnabled() && IsVisible();
}



void UI::Control::Base::BoxUpdateRequest()
{
	BoxUpdateIsRequested = true;
}
void UI::Control::Base::BoxUpdateRequestRecursive()
{
	BoxUpdateRequest();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> BoxUpdateRequestRecursive();
	}
}
void UI::Control::Base::BoxUpdateResolve()
{
	if (BoxUpdateIsRequested)
	{
		BoxUpdate();
	}
}
void UI::Control::Base::BoxUpdate()
{
	if (Parent == nullptr) { return; }

	BoxDisplay = Anchor.Calculate(Parent -> BoxContent);

	BoxBoarder.Min = BoxDisplay.Min + AnchorBoarder.Min;
	BoxBoarder.Max = BoxDisplay.Max - AnchorBoarder.Max;

	BoxContent.Min = BoxBoarder.Min + AnchorPadding.Min;
	BoxContent.Max = BoxBoarder.Max - AnchorPadding.Max;

	BoxUpdateIsRequested = false;
}



void UI::Control::Base::AutoAnchorUpdateResolve()
{
	if (AutoAnchorUpdateIsRequested)
	{
		AutoAnchorUpdate();
	}
}
void UI::Control::Base::AutoAnchorUpdateRequest()
{
	AutoAnchorUpdateIsRequested = true;
}
void UI::Control::Base::AutoAnchorUpdate()
{
	if (!IsVisible()) { return; }

	switch (AutoAnchorXType)
	{
		case EAutoAnchorType::None: break;
		default: break;
	}

	switch (AutoAnchorYType)
	{
		case EAutoAnchorType::None: break;
		case EAutoAnchorType::StackMin:		AutoAnchorUpdate_Y_StackMin(); break;
		case EAutoAnchorType::StackMinFit:	AutoAnchorUpdate_Y_StackMinFit(); break;
		default: break;
	}

	AutoAnchorUpdateIsRequested = false;
}

void UI::Control::Base::AutoAnchorUpdate_Y_StackMin()
{
	float y = 0.0f;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (Children[i] == nullptr) { continue; }
		Base & control = *Children[i];
		if (!control.IsVisible()) { continue; }
		control.Anchor.Y.AnchorMin(y);
		y = control.Anchor.Y.GetMinSize();
		control.BoxUpdate(); // is this needed here ?

		// AutoAnchor Children might need to update their Box again ?
		// their Sizes stay the same, only their Y Offset changes
		// Child BoxUpdate Anchor is bascially ignored / overridden
	}
}
void UI::Control::Base::AutoAnchorUpdate_Y_StackMinFit()
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
	BoxUpdateRequestRecursive();
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
void UI::Control::Base::ColorUpdateResolve()
{
	if (ColorUpdateIsRequested)
	{
		ColorUpdate();
	}
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
	ColorUpdateIsRequested = false;
}



void UI::Control::Base::DisplayPut() const
{
	if (Manager != nullptr && Display)
	{
		Inst::Data data;
		data.Layer = Depth();
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
}
void UI::Control::Base::DisplayHide()
{
	Display = false;
}

void UI::Control::Base::DisplayUpdateRequest()
{
	DisplayUpdateIsRequested = true;
}
void UI::Control::Base::DisplayUpdateRequestRecursive()
{
	DisplayUpdateRequest();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> DisplayUpdateRequestRecursive();
	}
}
void UI::Control::Base::DisplayUpdateResolve()
{
	if (DisplayUpdateIsRequested)
	{
		DisplayUpdate();
	}
}
void UI::Control::Base::DisplayUpdate()
{
	if (IsDrawable())
	{
		DisplayShow();
	}
	else
	{
		DisplayHide();
	}
	DisplayUpdateIsRequested = false;
}



void UI::Control::Base::Update()
{
	AutoAnchorUpdateResolve();
	BoxUpdateResolve();
	ColorUpdateResolve();
	DisplayUpdateResolve();
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

	float margin = 2.5f;
	float boarder = 2.0f;
	float padding = 2.5f;

	AnchorMargin = BoxF2(VectorF2(margin, margin), VectorF2(margin, margin));
	AnchorBoarder = BoxF2(VectorF2(boarder, boarder), VectorF2(boarder, boarder));
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));
}



UI::Control::Base * UI::Control::Base::FindHover(const VectorF2 & mouse)
{
	if (!IsThisVisible()) { return nullptr; }
	if (!IsEnabled()) { return nullptr; }
	if (!BoxDisplay.ContainsExclusive(mouse).All(true)) { return nullptr; }

	// check BoxContent before checking children ?
	Base * control = nullptr;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Base * c = Children[i] -> FindHover(mouse);
		if (c == nullptr) { continue; }
		if (control == nullptr || ((c -> Depth()) < (control -> Depth())))
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



void UI::Control::Base::RelayHover(HoverArgs args) { (void)args; }
void UI::Control::Base::RelayClick(ClickArgs args) { (void)args; }
void UI::Control::Base::RelayScroll(ScrollArgs args) { (void)args; }
void UI::Control::Base::RelayDrag(DragArgs args) { (void)args; }
void UI::Control::Base::RelayKey(KeyArgs args) { (void)args; }
void UI::Control::Base::RelayText(TextArgs args) { (void)args; }
