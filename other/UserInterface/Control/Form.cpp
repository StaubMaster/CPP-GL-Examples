#include "Control/Form.hpp"
#include "UIManager.hpp"
#include "AnchorEnum.hpp"



		UI::Manager *			UI::Control::Form::_Manager()			{ if (Window_ == nullptr) { return nullptr; } return Window_ -> Manager_; }
		UI::Manager *			UI::Control::Form::_Manager()	const	{ if (Window_ == nullptr) { return nullptr; } return Window_ -> Manager_; }



#include "Control/General/Base.hpp"
void UI::Control::Form::ChildClear()
{
	Control_Container::ChildClear();
	AutoAnchorUpdateRequest();
}
void UI::Control::Form::ChildRemove(Base & control)
{
	Control_Container::ChildRemove(control);
	AutoAnchorUpdateRequest();
}
void UI::Control::Form::ChildInsert(Base & control)
{
	Control_Container::ChildInsert(control);
	control.ChangeFormRecursive(this);

	control.DisplayUpdateRequest();
	control.AnchorUpdateRequest();
	AutoAnchorUpdateRequest();
}

#include "Display/DisplayPosition.hpp"
#include "HoverArgs.hpp"
bool UI::Control::Form::Check(const DisplayPosition & display_pos) const
{
	if (!IsThisVisible()) { return false; }
	if (!IsEnabled()) { return false; }

	const VectorF2 & pos = display_pos.Buffer.Corner;
	if (!BoxDisplay().ContainsExclusive(pos).All(true)) { return false; }

	return true;
}
UI::Control::Base * UI::Control::Form::Find(const DisplayPosition & display_pos)
{
	if (!Check(display_pos)) { return nullptr; }

	if (!IsThisVisible()) { return nullptr; }
	if (!IsEnabled()) { return nullptr; }
	const VectorF2 & pos = display_pos.Buffer.Corner;
	if (!BoxDisplay().ContainsExclusive(pos).All(true)) { return nullptr; }

	// check BoxContent before checking children ?
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
	return nullptr;
}

UI::Control::Base * UI::Control::Form::Hovering() const { return Hovering_; }
UI::Control::Base * UI::Control::Form::Selected() const { return Selected_; }
void UI::Control::Form::HoveringChange(UI::Control::Base * control, const DisplayPosition & display_pos)
{
	if (Hovering_ != control)
	{
		if (Hovering_ != nullptr) { Hovering_ -> RelayHover(HoverArgs(HoverType::Leave, display_pos)); }
		Hovering_ = control;
		if (Hovering_ != nullptr) { Hovering_ -> RelayHover(HoverArgs(HoverType::Enter, display_pos)); }
	}
	else
	{
		if (Hovering_ != nullptr) { Hovering_ -> RelayHover(HoverArgs(HoverType::Move, display_pos)); }
	}
}
void UI::Control::Form::SelectedChange()
{
	Selected_ = Hovering_;
}
void UI::Control::Form::HoveringUpdate(const DisplayPosition & display_pos)
{
	UI::Control::Base * control = Find(display_pos);
	HoveringChange(control, display_pos);
}
void UI::Control::Form::SelectedUpdate()
{
	SelectedChange();
}



bool UI::Control::Form::IsVisible() const
{
	return Control_Display::IsVisible();
}
void UI::Control::Form::Show()
{
	Control_Display::Show();
}
void UI::Control::Form::Hide()
{
	Control_Display::Hide();
}



unsigned int UI::Control::Form::Layer() const
{
	return 0;
}

unsigned int UI::Control::Form::LayerLimit() const
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

void UI::Control::Form::DepthChange(float depth)
{
	Depth_ = depth;
}
float UI::Control::Form::Depth(float depth) const
{
	if (Window_ == nullptr) { return 0.0f; }
	depth = Window_ -> Depth(depth);
	depth = depth + Depth_;
	return depth;
}



void UI::Control::Form::AnchorUpdate()
{
	Control_Display::AnchorUpdate();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> AnchorUpdateRequest();
	}
}



bool UI::Control::Form::MetaIs() const
{
	return (Window_ != nullptr);
}
BoxF2 UI::Control::Form::MetaBoxBoarder() const
{
	if (Window_ != nullptr) { return Window_ -> Box(); }
	return BoxF2();
}
BoxF2 UI::Control::Form::MetaBoxContent() const
{
	if (Window_ != nullptr) { return Window_ -> Box(); }
	return BoxF2();
}



void UI::Control::Form::AutoAnchorUpdate_Y_StackMin()
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

ColorF4 UI::Control::Form::Color() const
{
	return ColorF4(0.75f, 0.75f, 0.75f);
}



void UI::Control::Form::DisplayPut() const
{
//	if (_Manager() != nullptr && Parent != nullptr && Display)
//	if (_Manager() != nullptr && Window_ != nullptr && IsOpaque())
	if (_Manager() != nullptr && MetaIs() && IsOpaque())
	{
		UI::ControlGraphics::Inst::Data data;
		data.Layer = -Depth();
		data.Box = BoxDisplay();
		data.Color = Color();
		//data.Bound = Window_ -> Box();
		data.Bound = MetaBoxBoarder();
		_Manager() -> ControlManager.InstancePut(data);
	}
}
void UI::Control::Form::DisplayPutRecursive() const
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

void UI::Control::Form::DisplayUpdate()
{
	Control_Display::DisplayUpdate();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> DisplayUpdateRequest();
		// AutoAnchorUpdateRequest() ?
	}
}



void UI::Control::Form::UpdateRecursive()
{
	Update();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateRecursive();
	}
}



UI::Control::Form::Form()
	: Control_Display()
	, IsMovable(true)
	, IsResizable(true)
	, ChangingBoxType(EBoxChangeType::None)
{
	// give this stuff to Base ?
	Anchor.X.Anchor = AnchorType::None;
	Anchor.Y.Anchor = AnchorType::None;
//	AnchorSize = VectorF2(480, 360);
	AnchorSize = VectorF2(360, 240);
	AnchorNormal = VectorF2(0.5, 0.5);
}



UI::Control::Form::EBoxChangeType UI::Control::Form::FindChangingArea(VectorF2 mouse) const
{
	BoxF2 BoxBoarder;
	BoxBoarder.Min = BoxDisplay().Min + 10.0f;
	BoxBoarder.Max = BoxDisplay().Max - 10.0f;

	BoxF2 MinX_Box(VectorF2(BoxDisplay().Min.X, BoxDisplay().Min.Y), VectorF2(BoxBoarder  .Min.X, BoxDisplay().Max.Y));
	BoxF2 MaxX_Box(VectorF2(BoxBoarder  .Max.X, BoxDisplay().Min.Y), VectorF2(BoxDisplay().Max.X, BoxDisplay().Max.Y));
	BoxF2 MinY_Box(VectorF2(BoxDisplay().Min.X, BoxDisplay().Min.Y), VectorF2(BoxDisplay().Max.X, BoxBoarder  .Min.Y));
	BoxF2 MaxY_Box(VectorF2(BoxDisplay().Min.X, BoxBoarder  .Max.Y), VectorF2(BoxDisplay().Max.X, BoxDisplay().Max.Y));

	bool MinX_Hovering = MinX_Box.ContainsExclusive(mouse).All(true);
	bool MinY_Hovering = MinY_Box.ContainsExclusive(mouse).All(true);
	bool MaxX_Hovering = MaxX_Box.ContainsExclusive(mouse).All(true);
	bool MaxY_Hovering = MaxY_Box.ContainsExclusive(mouse).All(true);

	if (MinX_Hovering || MaxX_Hovering || MinY_Hovering || MaxY_Hovering)
	{
		if (IsResizable)
		{
			if (MinX_Hovering && !(MinY_Hovering || MaxY_Hovering)) { return EBoxChangeType::ResizeMinX; }
			if (MaxX_Hovering && !(MinY_Hovering || MaxY_Hovering)) { return EBoxChangeType::ResizeMaxX; }
			if (MinY_Hovering && !(MinX_Hovering || MaxX_Hovering)) { return EBoxChangeType::ResizeMinY; }
			if (MaxY_Hovering && !(MinX_Hovering || MaxX_Hovering)) { return EBoxChangeType::ResizeMaxY; }
			
			if (MinX_Hovering && MinY_Hovering) { return EBoxChangeType::ResizeMinMin; }
			if (MinX_Hovering && MaxY_Hovering) { return EBoxChangeType::ResizeMinMax; }
			if (MaxX_Hovering && MinY_Hovering) { return EBoxChangeType::ResizeMaxMin; }
			if (MaxX_Hovering && MaxY_Hovering) { return EBoxChangeType::ResizeMaxMax; }
		}
	}
	else
	{
		if (IsMovable)
		{
			return EBoxChangeType::Move;
		}
	}
	return EBoxChangeType::None;
}

void UI::Control::Form::ChangeAnchorBox(BoxF2 box, EBoxChangeType type)
{
	if (type == EBoxChangeType::None) { return; }
	if (Window_ != nullptr)
	{
		// when moving, keep size
		// when resizing, keep other side

		BoxF2 other_box;
		other_box.Min = (Window_ -> Box().Min) + AnchorMargin.Min;
		other_box.Max = (Window_ -> Box().Max) - AnchorMargin.Max;

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
		Anchor.UpdateO(Window_ -> Box(), box);
		//BoxUpdateRequestRecursive();
		AnchorUpdateRequest();
	}
}



#include "Control/Graphics/Manager.hpp"
#include "User/MouseArgs.hpp"
#include "User/KeyBoardArgs.hpp"
#include "HoverArgs.hpp"
/* put into Manager
	Cursors flicked when moving
	put into Manager, Cursor should stay the same until changing ends
	dont do any Events (drag/move) while changing
*/
void UI::Control::Form::RelayHover(HoverArgs args)
{
	/*if (args == HoverArgs::Enter)
	{
		Manager -> Cursor.UseResizeH();
	}*/
	if (args.Type == HoverType::Leave)
	{
		_Manager() -> Cursor.UseDefault();
	}
	if (args.Type == HoverType::Move)
	{
		EBoxChangeType type = FindChangingArea(_Manager() -> Cursor.Position);
		if (type == EBoxChangeType::Move) { _Manager() -> Cursor.UseDefault(); }
		else if (type == EBoxChangeType::ResizeMinX) { _Manager() -> Cursor.UseBoxEdge(0); }
		else if (type == EBoxChangeType::ResizeMinY) { _Manager() -> Cursor.UseBoxEdge(1); }
		else if (type == EBoxChangeType::ResizeMaxX) { _Manager() -> Cursor.UseBoxEdge(2); }
		else if (type == EBoxChangeType::ResizeMaxY) { _Manager() -> Cursor.UseBoxEdge(3); }
		else if (type == EBoxChangeType::ResizeMinMin) { _Manager() -> Cursor.UseBoxCorn(0); }
		else if (type == EBoxChangeType::ResizeMaxMin) { _Manager() -> Cursor.UseBoxCorn(1); }
		else if (type == EBoxChangeType::ResizeMinMax) { _Manager() -> Cursor.UseBoxCorn(2); }
		else if (type == EBoxChangeType::ResizeMaxMax) { _Manager() -> Cursor.UseBoxCorn(3); }
		else { _Manager() -> Cursor.UseDefault(); }
	}
}
void UI::Control::Form::RelayDrag(DragArgs args)
{
	// Check that no Control is being Hovered
	if (args.Action == Action::Press)
	{
		ChangingBoxRel.Min = args.Position.Buffer.Corner - BoxDisplay().Min;
		ChangingBoxRel.Max = args.Position.Buffer.Corner - BoxDisplay().Max;

		/* Resize area
			in vscode, the cursor needs to be a bit inside of the window to resize
			in firefox, the cursor needs to be a bit outside of the window to resize
		*/

		ChangingBoxType = FindChangingArea(args.Position.Buffer.Corner);
	}
	else if (args.Action == Action::Repeat)
	{
		// when changing would make the Box go outside of the Window
		// keep it inside of the Window (with MBP) and lock it to that Edge
		// when changing makes a Edge of the Box be away from whe Window Boarder
		// make it unlocked from that Edge
		// also make things lock to eachother ?

		if (ChangingBoxType != EBoxChangeType::None)
		{
			const VectorF2 & mouse = args.Position.Buffer.Corner;
			BoxF2 box = BoxDisplay();
			if (ChangingBoxType == EBoxChangeType::Move)
			{
				box.Min = mouse - ChangingBoxRel.Min;
				box.Max = mouse - ChangingBoxRel.Max;
			}
			else if (ChangingBoxType == EBoxChangeType::ResizeMinX) { box.Min.X = mouse.X; }
			else if (ChangingBoxType == EBoxChangeType::ResizeMaxX) { box.Max.X = mouse.X; }
			else if (ChangingBoxType == EBoxChangeType::ResizeMinY) { box.Min.Y = mouse.Y; }
			else if (ChangingBoxType == EBoxChangeType::ResizeMaxY) { box.Max.Y = mouse.Y; }
			else if (ChangingBoxType == EBoxChangeType::ResizeMinMin) { box.Min.X = mouse.X; box.Min.Y = mouse.Y; }
			else if (ChangingBoxType == EBoxChangeType::ResizeMinMax) { box.Min.X = mouse.X; box.Max.Y = mouse.Y; }
			else if (ChangingBoxType == EBoxChangeType::ResizeMaxMin) { box.Max.X = mouse.X; box.Min.Y = mouse.Y; }
			else if (ChangingBoxType == EBoxChangeType::ResizeMaxMax) { box.Max.X = mouse.X; box.Max.Y = mouse.Y; }
			ChangeAnchorBox(box, ChangingBoxType);
		}
	}
	else if (args.Action == Action::Release)
	{
		ChangingBoxType = EBoxChangeType::None;
	}
}
