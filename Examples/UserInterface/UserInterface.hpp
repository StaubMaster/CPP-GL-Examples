#ifndef  CONTEXT_1_HPP
# define CONTEXT_1_HPP

# include "General/ContextBase.hpp"
# include "UserInterfaceMenu0.hpp"

# include "UIManager.hpp"

struct Context1 : public ContextBase
{
UI::Manager				UIManager;

Context1Menu			Menu;

~Context1();
Context1();

void Make();

void Init() override;
void Free() override;

void Resize(DisplaySize display_size) override;
void Frame(FrameTime frame_time) override;

void	MouseMove(MoveArgs args) override;
void	MouseClick(ClickArgs args) override;
void	MouseScroll(ScrollArgs args) override;
void	MouseDrag(DragArgs args) override;
void	KeyBoardKey(KeyArgs args) override;
void	KeyBoardText(TextArgs args) override;
};

#endif