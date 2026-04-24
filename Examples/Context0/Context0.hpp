#ifndef  CONTEXT_0_HPP
# define CONTEXT_0_HPP

# include "ContextBase.hpp"
# include "Context0Menu.hpp"

# include "Control/Base/Manager.hpp"

# include "Text/Manager.hpp"

struct Context0 : public ContextBase
{
UI::Control::Manager	ControlManager;
UI::Text::Manager		TextManager;

Context0Menu			Menu;

~Context0();
Context0();

void	Make();

void	Init() override;
void	Free() override;

void	Resize(DisplaySize display_size) override;
void	Frame(FrameTime frame_time) override;

void	MouseScroll(ScrollArgs args) override;
void	MouseClick(ClickArgs args) override;
void	MouseDrag(DragArgs args) override;
void	KeyBoardKey(KeyArgs args) override;
};

#endif