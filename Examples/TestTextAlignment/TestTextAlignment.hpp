#ifndef  TEST_TEXT_ALIGNMENT_HPP
# define TEST_TEXT_ALIGNMENT_HPP

# include "ContextBase.hpp"

# include "Control/Base/Manager.hpp"
# include "ControlsInclude.hpp"

# include "Text/Manager.hpp"

struct ContextTestTextAlignment : public ContextBase
{
UI::Control::Manager	ControlManager;
UI::Text::Manager		TextManager;

~ContextTestTextAlignment();
ContextTestTextAlignment();

void Make();

void Init() override;
void Free() override;

void Resize(DisplaySize display_size) override;
void Frame(FrameTime frame_time) override;

void MouseScroll(ScrollArgs args) override;
void MouseClick(ClickArgs args) override;
void MouseDrag(DragArgs args) override;
void KeyBoardKey(KeyArgs args) override;
};

#endif