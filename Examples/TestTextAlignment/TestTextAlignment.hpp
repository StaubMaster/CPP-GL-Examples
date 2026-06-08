#ifndef  TEST_TEXT_ALIGNMENT_HPP
# define TEST_TEXT_ALIGNMENT_HPP

# include "General/ContextBase.hpp"

# include "UIManager.hpp"

struct ContextTestTextAlignment : public ContextBase
{
UI::Manager				UIManager;

~ContextTestTextAlignment();
ContextTestTextAlignment();

void	Make();

void	Init() override;
void	Free() override;

void	TextAlignment();

void	Frame(FrameTime frame_time) override;
void	Resize(DisplaySize display_size) override;

void	MouseMove(MoveArgs args) override;
void	MouseClick(ClickArgs args) override;
void	MouseScroll(ScrollArgs args) override;
void	MouseDrag(DragArgs args) override;
void	KeyBoardKey(KeyArgs args) override;
void	KeyBoardText(TextArgs args) override;
};

#endif