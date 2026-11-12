#include "Base.hpp"
#include "Control/Form.hpp"
#include "UIManager.hpp"
#include "Graphics/Inst/Data.hpp"



		UI::Manager *			UI::Control::Base::_Manager()			{ if (Form_ == nullptr) { return nullptr; } return Form_ -> _Manager(); }
		UI::Manager *			UI::Control::Base::_Manager()	const	{ if (Form_ == nullptr) { return nullptr; } return Form_ -> _Manager(); }
		UI::Control::Window *	UI::Control::Base::_Window()			{ if (Form_ == nullptr) { return nullptr; } return Form_ -> _Window(); }
const	UI::Control::Window *	UI::Control::Base::_Window()	const	{ if (Form_ == nullptr) { return nullptr; } return Form_ -> _Window(); }
		UI::Control::Form *		UI::Control::Base::_Form()				{ return Form_; }
const	UI::Control::Form *		UI::Control::Base::_Form()		const	{ return Form_; }

void UI::Control::Base::AssignPointers(Base & other)
{
	other.Parent = this;
	other.AssignPointersRecursive(Form_);
}
void UI::Control::Base::AssignPointers(UI::Control::Form * form)
{
	Form_ = form;
}
void UI::Control::Base::AssignPointersRecursive(UI::Control::Form * form)
{
	AssignPointers(form);
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> AssignPointersRecursive(form);
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

	control.DisplayUpdateRequest();

	control.AnchorUpdateRequest();

	//control.BoxUpdateRequestRecursive();

	//control.ColorUpdateRequestRecursive();

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



bool UI::Control::Base::IsEnabled() const
{
	return IsEnabled_;
}
void UI::Control::Base::Enable()
{
	IsEnabled_ = true;
	//ColorUpdateRequestRecursive();
}
void UI::Control::Base::Disable()
{
	IsEnabled_ = false;
	//ColorUpdateRequestRecursive();
}

bool UI::Control::Base::IsThisVisible() const
{
	return IsVisible_;
}
void UI::Control::Base::Show()
{
	IsVisible_ = true;
	//DisplayUpdateRequestRecursive();
	DisplayUpdateRequest();
	if (Parent != nullptr)
	{
		Parent -> AutoAnchorUpdateRequest();
	}
}
void UI::Control::Base::Hide()
{
	IsVisible_ = false;
	//DisplayUpdateRequestRecursive();
	DisplayUpdateRequest();
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
bool UI::Control::Base::IsDisplay() const
{
	return IsOpaque() && IsVisible();
}
/*bool UI::Control::Base::IsThisInteractible() const
{
	return IsEnabled() && IsDisplay();
}*/
bool UI::Control::Base::IsInteractible() const
{
	return IsEnabled() && IsVisible();
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
/*float UI::Control::Base::Depth() const
{
	// return NaN ?
	if (Window == nullptr) { return 0.0f; }
	if (Form == nullptr) { return 0.0f; }
	return -((Layer() * (Window -> DepthSize)) + (Form -> DepthOffset));
}*/
float UI::Control::Base::Depth(float diff) const
{
	if (_Window() == nullptr) { return 0.0f; }
	if (_Form() == nullptr) { return 0.0f; }
	return -(((Layer() + diff) * (_Window() -> DepthSize)) + (_Form() -> DepthOffset)); // put this Calculation in Form ?
}



void UI::Control::Base::AnchorUpdateRequest()
{
	AnchorUpdateIsRequested = true;
}
void UI::Control::Base::AnchorUpdate()
{
	if (Parent == nullptr) { return; }

	Anchor.UpdateO(Parent -> BoxContent());

	AnchorUpdateIsRequested = false;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> AnchorUpdateRequest();
	}
}



/*void UI::Control::Base::BoxUpdateRequest()
{
	BoxUpdateIsRequested = true;
}*/
/*void UI::Control::Base::BoxUpdate()
{
	if (Parent == nullptr) { return; }

	Anchor.UpdateO(Parent -> BoxContent());

//	Anchor.UpdateO(Parent -> BoxContent);
//	BoxDisplay = Anchor.ToInnerBox(Parent -> BoxContent);
//
//	BoxBoarder.Min = BoxDisplay.Min + AnchorBoarder.Min;
//	BoxBoarder.Max = BoxDisplay.Max - AnchorBoarder.Max;
//
//	BoxContent.Min = BoxBoarder.Min + AnchorPadding.Min;
//	BoxContent.Max = BoxBoarder.Max - AnchorPadding.Max;

	BoxUpdateIsRequested = false;
}*/

BoxF2 UI::Control::Base::BoxDisplay() const
{
	if (Parent == nullptr) { return BoxF2(); }
	return Anchor.ToInnerBox(Parent -> BoxContent());
}
BoxF2 UI::Control::Base::BoxBoarder() const
{
	if (Parent == nullptr) { return BoxF2(); }
	BoxF2 box = BoxDisplay();
	return BoxF2(
		box.Min + AnchorBoarder.Min,
		box.Max - AnchorBoarder.Max
	);
}
BoxF2 UI::Control::Base::BoxContent() const
{
	if (Parent == nullptr) { return BoxF2(); }
	BoxF2 box = BoxBoarder();
	return BoxF2(
		box.Min + AnchorPadding.Min,
		box.Max - AnchorPadding.Max
	);
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
		//case EAutoAnchorType::StackMinFit:	AutoAnchorUpdate_Y_StackMinFit(); break;
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
	}
	AnchorUpdateRequest();
}
/*void UI::Control::Base::AutoAnchorUpdate_Y_StackMinFit()
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
	//BoxUpdateRequestRecursive();
	AnchorUpdateRequest();
}*/



/*void UI::Control::Base::ColorUpdateRequest()
{
	ColorUpdateIsRequested = true;
}*/
/*void UI::Control::Base::ColorUpdate()
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
}*/
ColorF4 UI::Control::Base::Color() const
{
	if (_Manager() == nullptr)
	{
		return ColorDefault;
	}
	else
	{
		if (_Manager() -> Hovering != this)
		{
			return ColorDefault;
		}
		else
		{
			return ColorHover;
		}
	}
}



void UI::Control::Base::DisplayPut() const
{
//	if (_Manager() != nullptr && Parent != nullptr && Display)
	if (_Manager() != nullptr && Parent != nullptr && IsOpaque())
	{
		Inst::Data data;
		data.Layer = Depth();
		data.Box = BoxDisplay();
		data.Color = Color();
		data.Bound = Parent -> BoxBoarder();
		_Manager() -> ControlManager.InstancePut(data);
	}
}
void UI::Control::Base::DisplayPutRecursive() const
{
	if (IsThisVisible())
	{
		DisplayPut();
		for (unsigned int i = 0; i < Children.Count(); i++)
		{
			Children[i] -> DisplayPutRecursive();
		}
	}
}

void UI::Control::Base::DisplayShow() { }
void UI::Control::Base::DisplayHide() { }

void UI::Control::Base::DisplayUpdateRequest()
{
	DisplayUpdateIsRequested = true;
}
void UI::Control::Base::DisplayUpdate()
{
	if (IsDisplay())	{ DisplayShow(); }
	else				{ DisplayHide(); }

	DisplayUpdateIsRequested = false;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> DisplayUpdateRequest();
	}
}



void UI::Control::Base::Update()
{
	//AutoAnchorUpdateResolve();
	if (AutoAnchorUpdateIsRequested)	{ AutoAnchorUpdate(); }

	//BoxUpdateResolve();

	//AnchorUpdateResolve();
	if (AnchorUpdateIsRequested)		{ AnchorUpdate(); }

	//ColorUpdateResolve();

	//DisplayUpdateResolve();
	if (DisplayUpdateIsRequested)		{ DisplayUpdate(); }
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
	if (!BoxDisplay().ContainsExclusive(mouse).All(true)) { return nullptr; }

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
