#ifndef  SELECTOR_CONTEXT_HPP
# define SELECTOR_CONTEXT_HPP

# include "ContextBase.hpp"
# include "SelectorMenu.hpp"

# include "UIManager.hpp"

struct SelectorContext : public ContextBase
{
UI::Manager		UIManager;

SelectorMenu	Menu;

~SelectorContext();
SelectorContext();

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