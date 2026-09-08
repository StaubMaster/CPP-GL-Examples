#ifndef  USER_INTERFACE_CONTEXT_HPP
# define USER_INTERFACE_CONTEXT_HPP

# include "ContextBase.hpp"

# include "FrameTime.hpp"

# include "Control/Form.hpp"

# include "UIManager.hpp"

struct UserInterfaceContext : public ContextBase
{
	UI::Manager				UIManager;

	UI::Control::Form		JitterTest;

	~UserInterfaceContext();
	UserInterfaceContext();
	
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