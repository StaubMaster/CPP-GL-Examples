#ifndef  USER_INTERFACE_CONTEXT_HPP
# define USER_INTERFACE_CONTEXT_HPP

# include "ContextBase.hpp"
# include "Menu0.hpp"
# include "Menu1.hpp"
# include "Menu2.hpp"
# include "Menu3.hpp"

# include "UIManager.hpp"

struct UserInterfaceContext : public ContextBase
{
	UI::Manager				UIManager;
	
	UserInterfaceMenu0		Menu0;
	UserInterfaceMenu1		Menu1;
	UserInterfaceMenu2		Menu2;
	UserInterfaceMenu3		Menu3;

	~UserInterfaceContext();
	UserInterfaceContext();
	
	void	Make();
	void	Menu1Toggle(ClickArgs args);
	void	Menu2Toggle(ClickArgs args);
	void	Menu3Toggle(ClickArgs args);
	
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