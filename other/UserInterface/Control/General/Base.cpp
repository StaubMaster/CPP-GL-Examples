#include "Base.hpp"
#include "Control/Form.hpp"
#include "UIManager.hpp"
#include "Control/Graphics/Inst/Data.hpp"



		UI::Manager *			UI::Control_::Base::_Manager()			{ if (Parent_ == nullptr) { return nullptr; } return Parent_ -> _Manager(); }
		UI::Manager *			UI::Control_::Base::_Manager()	const	{ if (Parent_ == nullptr) { return nullptr; } return Parent_ -> _Manager(); }
		UI::Control_::Window *	UI::Control_::Base::_Window()			{ if (Parent_ == nullptr) { return nullptr; } return Parent_ -> _Window(); }
const	UI::Control_::Window *	UI::Control_::Base::_Window()	const	{ if (Parent_ == nullptr) { return nullptr; } return Parent_ -> _Window(); }



float UI::Control_::Base::LayerDepth() const
{
	if (Parent_ == nullptr) { return 0.0f; }
	return Parent_ -> LayerDepth();
}
float UI::Control_::Base::DepthOffset() const
{
	if (Parent_ == nullptr) { return 0.0f; }
	return Parent_ -> DepthOffset();
}



bool UI::Control_::Base::MetaIs() const
{
	return (Parent_ != nullptr);
}
BoxF2 UI::Control_::Base::MetaBoxBoarder() const
{
	if (Parent_ != nullptr) { return Parent_ -> BoxBoarder(); }
	return BoxF2();
}
BoxF2 UI::Control_::Base::MetaBoxContent() const
{
	if (Parent_ != nullptr) { return Parent_ -> BoxContent(); }
	return BoxF2();
}
