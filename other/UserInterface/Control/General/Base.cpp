#include "Base.hpp"
#include "Control/Form.hpp"
#include "UIManager.hpp"
#include "Control/Graphics/Inst/Data.hpp"



		UI::Manager *			UI::Control::Base::_Manager()			{ if (Form_ == nullptr) { return nullptr; } return Form_ -> _Manager(); }
		UI::Manager *			UI::Control::Base::_Manager()	const	{ if (Form_ == nullptr) { return nullptr; } return Form_ -> _Manager(); }
		UI::Control::Window *	UI::Control::Base::_Window()			{ if (Form_ == nullptr) { return nullptr; } return Form_ -> Window_; }
const	UI::Control::Window *	UI::Control::Base::_Window()	const	{ if (Form_ == nullptr) { return nullptr; } return Form_ -> Window_; }

void UI::Control::Base::ChangeFormRecursive(UI::Control::Form * form)
{
	Form_ = form;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> ChangeFormRecursive(form);
	}
}



UI::Control::Base * UI::Control::Base::Parent() const
{
	return Parent_;
}

void UI::Control::Base::ChildClear()
{
	Control_Container::ChildClear();
	AutoAnchorUpdateRequest();
}
void UI::Control::Base::ChildRemove(Base & control)
{
	Control_Container::ChildRemove(control);
	AutoAnchorUpdateRequest();
}
void UI::Control::Base::ChildInsert(Base & control)
{
	Control_Container::ChildInsert(control);
	control.Parent_ = this;
	ChangeFormRecursive(Form_);

	control.DisplayUpdateRequest();
	control.AnchorUpdateRequest();
	AutoAnchorUpdateRequest();
}

#include "Display/DisplayPosition.hpp"
bool UI::Control::Base::Check(const DisplayPosition & display_pos) const
{
	if (!IsThisVisible()) { return false; }
	if (!IsEnabled()) { return false; }

	const VectorF2 & pos = display_pos.Buffer.Corner;
	if (!BoxDisplay().ContainsExclusive(pos).All(true)) { return false; }

	return true;
}
UI::Control::Base * UI::Control::Base::Find(const DisplayPosition & display_pos)
{
	if (!Check(display_pos)) { return nullptr; }

	Base * control = nullptr;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Base * c = Children[i] -> Find(display_pos);
		if (c == nullptr) { continue; }
		if (control == nullptr || ((c -> Depth()) > (control -> Depth())))
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



bool UI::Control::Base::IsVisible() const
{
	if (!IsThisVisible()) { return false; }
	if (Parent_ != nullptr) { return Parent_ -> IsVisible(); }
	if (Form_ != nullptr) { return Form_ -> IsVisible(); }
	return false;
}
void UI::Control::Base::Show()
{
	Control_Display::Show();
	if (Parent_ != nullptr) { Parent_ -> AutoAnchorUpdateRequest(); }
	if (Form_ != nullptr) { Form_ -> AutoAnchorUpdateRequest(); }
}
void UI::Control::Base::Hide()
{
	Control_Display::Hide();
	if (Parent_ != nullptr) { Parent_ -> AutoAnchorUpdateRequest(); }
	if (Form_ != nullptr) { Form_ -> AutoAnchorUpdateRequest(); }
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
	if (Parent_ != nullptr)
	{
		return (Parent_ -> Layer()) + 1;
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
float UI::Control::Base::Depth(float depth) const
{
	if (Form_ == nullptr) { return 0.0f; }
	depth = depth + (Layer());
	depth = Form_ -> Depth(depth);
	return depth;
}



void UI::Control::Base::AnchorUpdate()
{
	Control_Display::AnchorUpdate();
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

bool UI::Control::Base::MetaIs() const
{
	return (Parent_ != nullptr || Form_ != nullptr);
}
BoxF2 UI::Control::Base::MetaBoxBoarder() const
{
	if (Parent_ != nullptr) { return Parent_ -> BoxBoarder(); }
	if (Form_ != nullptr) { return Form_ -> BoxBoarder(); }
	return BoxF2();
}
BoxF2 UI::Control::Base::MetaBoxContent() const
{
	if (Parent_ != nullptr) { return Parent_ -> BoxContent(); }
	if (Form_ != nullptr) { return Form_ -> BoxContent(); }
	return BoxF2();
}



void UI::Control::Base::AutoAnchorUpdate_Y_StackMin()
{
	Base * control = nullptr;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (Children[i] == nullptr) { continue; }
		Base & c = *Children[i];
		if (!c.IsVisible()) { continue; }
		c.Make_Anchor_Y_Min(control);
		control = &c;
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
	if (Form_ == nullptr)
	{
		return ColorDefault;
	}
	else
	{
		if (Form_ -> Hovering() != this)
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
	if (_Manager() != nullptr && MetaIs() && IsOpaque())
	{
		UI::ControlGraphics::Inst::Data data;
		data.Layer = -Depth();
		data.Box = BoxDisplay();
		data.Color = Color();
		data.Bound = MetaBoxBoarder();
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
	Control_Display::DisplayUpdate();
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
