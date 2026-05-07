#ifndef  CONTEXT_1_HPP
# define CONTEXT_1_HPP

# include "ContextBase.hpp"
# include "Context1Menu.hpp"

# include "Control/Base/Manager.hpp"
# include "ControlsInclude.hpp"

# include "Text/Manager.hpp"

struct Context1 : public ContextBase
{
UI::Control::Manager	ControlManager;
UI::Text::Manager		TextManager;

Context1Menu			Menu;

~Context1();
Context1();

void Make();

void Init() override;
void Free() override;

void Resize(DisplaySize display_size) override;
void Frame(FrameTime frame_time) override;

void MouseClick(ClickArgs args) override;
void MouseDrag(DragArgs args) override;
void MouseScroll(ScrollArgs args) override;
void KeyBoardKey(KeyArgs args) override;
void KeyBoardText(TextArgs args);
};

#endif