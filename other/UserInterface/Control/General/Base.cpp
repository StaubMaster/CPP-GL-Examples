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

void UI::Control::Base::ChangeForm(UI::Control::Form * form)
{
	Form_ = form;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> ChangeForm(form);
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
	control.Parent = this;
	ChangeForm(Form_);
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



bool UI::Control::Base::IsVisible() const
{
	if (Parent != nullptr)
	{
		return IsThisVisible() && (Parent -> IsVisible());
	}
	if (Form_ != nullptr)
	{
		return IsThisVisible() && (Form_ -> IsVisible());
	}
	return ControlDisplay::IsVisible();
}
void UI::Control::Base::Show()
{
	ControlDisplay::Show();
	if (Parent != nullptr)
	{
		Parent -> AutoAnchorUpdateRequest();
	}
	if (Form_ != nullptr)
	{
		Form_ -> AutoAnchorUpdateRequest();
	}
}
void UI::Control::Base::Hide()
{
	ControlDisplay::Hide();
	if (Parent != nullptr)
	{
		Parent -> AutoAnchorUpdateRequest();
	}
	if (Form_ != nullptr)
	{
		Form_ -> AutoAnchorUpdateRequest();
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
	else if (Form_ != nullptr)
	{
		return (Form_ -> Layer()) + 1;
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



void UI::Control::Base::AnchorUpdate()
{
	if (Parent == nullptr && Form_ == nullptr) { return; }

	if (Form_ != nullptr) { Anchor.UpdateO(Form_ -> BoxContent()); }
	if (Parent != nullptr) { Anchor.UpdateO(Parent -> BoxContent()); }

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
	if (Parent != nullptr) { return Anchor.ToInnerBox(Parent -> BoxContent()); }
	if (Form_ != nullptr) { return Anchor.ToInnerBox(Form_ -> BoxContent()); }
	return BoxF2();
}
BoxF2 UI::Control::Base::BoxBoarder() const
{
	if (Form_ == nullptr && Parent == nullptr) { return BoxF2(); }
	BoxF2 box = BoxDisplay();
	return BoxF2(
		box.Min + AnchorBoarder.Min,
		box.Max - AnchorBoarder.Max
	);
}
BoxF2 UI::Control::Base::BoxContent() const
{
	if (Form_ == nullptr && Parent == nullptr) { return BoxF2(); }
	BoxF2 box = BoxBoarder();
	return BoxF2(
		box.Min + AnchorPadding.Min,
		box.Max - AnchorPadding.Max
	);
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
	if (_Form() == nullptr)
	{
		return ColorDefault;
	}
	else
	{
		if (_Form() -> Hovering() != this)
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
	if (_Manager() != nullptr && (Parent != nullptr || Form_ != nullptr) && IsOpaque())
	{
		Inst::Data data;
		data.Layer = Depth();
		data.Box = BoxDisplay();
		data.Color = Color();
		if (Form_ != nullptr) { data.Bound = Form_ -> BoxBoarder(); }
		if (Parent != nullptr) { data.Bound = Parent -> BoxBoarder(); }
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

void UI::Control::Base::DisplayUpdate()
{
	ControlDisplay::DisplayUpdate();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> DisplayUpdateRequest();
		// AutoAnchorUpdateRequest() ?
	}
}



void UI::Control::Base::UpdateRecursive()
{
	Update();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateRecursive();
	}
}



#include "Display/DisplayPosition.hpp"
UI::Control::Base * UI::Control::Base::Find(const DisplayPosition & display_pos)
{
	if (!IsThisVisible()) { return nullptr; }
	if (!IsEnabled()) { return nullptr; }

	const VectorF2 & mouse = display_pos.Buffer.Corner;
	if (!BoxDisplay().ContainsExclusive(mouse).All(true)) { return nullptr; }

	// check BoxContent before checking children ?
	Base * control = nullptr;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Base * c = Children[i] -> Find(display_pos);
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



UI::Control::Base::~Base()
{
	/*for (unsigned int i = 0; i < Children.Count(); i++)
	{
		delete Children[i];
	}*/
}
UI::Control::Base::Base()
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
