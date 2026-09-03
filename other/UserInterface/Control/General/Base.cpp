#include "Base.hpp"
#include "UIManager.hpp"



void UI::Control::Base::ChangePointers(Base & control)
{
	control.Parent = this;
	control.ChangeManagerRecursive(Manager);
	control.ChangeManagerRecursive(Window);
	control.ChangeManagerRecursive(Form);
}

void UI::Control::Base::ChangeManager(UI::Manager * manager)
{
	Manager = manager;
}
void UI::Control::Base::ChangeManager(UI::Control::Window * window)
{
	Window = window;
}
void UI::Control::Base::ChangeManager(UI::Control::Form * form)
{
	Form = form;
}

void UI::Control::Base::ChangeManagerRecursive(UI::Manager * manager)
{
	ChangeManager(manager);
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> ChangeManagerRecursive(manager);
	}
}
void UI::Control::Base::ChangeManagerRecursive(UI::Control::Window * window)
{
	ChangeManager(window);
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> ChangeManagerRecursive(window);
	}
}
void UI::Control::Base::ChangeManagerRecursive(UI::Control::Form * form)
{
	ChangeManager(form);
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> ChangeManagerRecursive(form);
	}
}



void UI::Control::Base::ChildInsert(Base & control)
{
	ChangePointers(control);
	Children.Insert(&control);
	control.DisplayChangeRequest();
	control.BoxUpdateRequest();
	control.ColorUpdateRequest();
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
void UI::Control::Base::ChildClear()
{
	Children.Clear();
	AutoAnchorUpdateRequest();
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



void UI::Control::Base::CalcLayer()
{
	if (Parent != nullptr)
	{
		Layer = (Parent -> Layer) + 1;
	}
	else
	{
		Layer = 0;
	}
}
void UI::Control::Base::CalcLayerRecursive()
{
	CalcLayer();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Base * control = Children[i];
		if (control == nullptr) { continue; }
		control -> CalcLayerRecursive();
	}
}

// CalcLayerLimit() then store
// store in Form ?
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

#include "Control/Form.hpp" // this is only included for Depth
// put Depth stuff in seperate file ?
void UI::Control::Base::AssignDepth()
{
	if (Window == nullptr) { return; }
	if (Form == nullptr) { return; }

	float size = Window -> DepthSize;
	float offset = Form -> DepthOffset;
	float layer = Layer;

	Depth = -((layer * size) + offset);
}
void UI::Control::Base::AssignDepthRecursive()
{
	AssignDepth();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Base * control = Children[i];
		if (control == nullptr) { continue; }
		control -> AssignDepthRecursive();
	}
}



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
	if (Parent != nullptr)
	{
		Parent -> AutoAnchorUpdateRequest();
	}
}
void UI::Control::Base::Hide()
{
	_Visible = false;
	DisplayChangeRequest();
	if (Parent != nullptr)
	{
		Parent -> AutoAnchorUpdateRequest();
	}
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



void UI::Control::Base::AutoAnchorUpdateResolve()
{
	if (!IsVisible()) { return; }
	if (AutoAnchorUpdateIsRequested)
	{
		if (AutoAnchorYType != EAutoAnchorType::None || AutoAnchorXType != EAutoAnchorType::None)
		{
			AutoAnchorUpdate();
			if (Parent != nullptr)
			{
				Parent -> AutoAnchorUpdateRequest();
			}
		}
		AutoAnchorUpdateIsRequested = false;
	}
}
void UI::Control::Base::AutoAnchorUpdateRequest()
{
	AutoAnchorUpdateIsRequested = true;
}

#include <iostream>
// this is called a lot every frame
// why ?
void UI::Control::Base::AutoAnchorUpdate()
{
	static unsigned int num = 0;
	std::cout << "UI::Control::Base::AutoAnchorUpdate() " << num << '\n';
	num++;

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
}
void UI::Control::Base::AutoAnchorUpdate_Y_StackMin()
{
	std::cout << "UI::Control::Base::AutoAnchorUpdate_Y_StackMin()\n";
	std::cout << "Children: " << Children.Count() << "\n";
	float y = 0.0f;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		std::cout << "y: " << y << '\n';
		if (Children[i] == nullptr) { continue; }
		Base & control = *Children[i];
		if (!control.IsVisible()) { continue; }
		control.Anchor.Y.AnchorMin(y);
		y = control.Anchor.Y.GetMinSize();
		//control.BoxUpdateRequest();
		control.BoxUpdate();
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
	AutoAnchorUpdateResolve();
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
	if (!_Visible) { return nullptr; }
	if (!_Enabled) { return nullptr; }
	if (!BoxDisplay.ContainsExclusive(mouse).All(true)) { return nullptr; }

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



void UI::Control::Base::RelayHover(HoverArgs args) { (void)args; }
void UI::Control::Base::RelayClick(ClickArgs args) { (void)args; }
void UI::Control::Base::RelayScroll(ScrollArgs args) { (void)args; }
void UI::Control::Base::RelayDrag(DragArgs args) { (void)args; }
void UI::Control::Base::RelayKey(KeyArgs args) { (void)args; }
void UI::Control::Base::RelayText(TextArgs args) { (void)args; }
