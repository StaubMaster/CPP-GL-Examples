#ifndef  CONTEXT_0_HPP
# define CONTEXT_0_HPP

# include "General/ContextBase.hpp"
# include "SelectorMenu.hpp"

# include "UIManager.hpp"

struct Context0 : public ContextBase
{
UI::Manager				UIManager;

Context0Menu			Menu;

~Context0();
Context0();

void	Make();

void	Init() override;
void	Free() override;

void	Resize(DisplaySize display_size) override;
void	Frame(FrameTime frame_time) override;

void	MouseMove(MoveArgs args) override;
void	MouseClick(ClickArgs args) override;
void	MouseScroll(ScrollArgs args) override;
void	MouseDrag(DragArgs args) override;
void	KeyBoardKey(KeyArgs args) override;
void	KeyBoardText(TextArgs args) override;
};

#endif