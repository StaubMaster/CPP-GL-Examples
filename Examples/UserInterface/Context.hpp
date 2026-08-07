#ifndef  USER_INTERFACE_CONTEXT_HPP
# define USER_INTERFACE_CONTEXT_HPP

# include "ContextBase.hpp"

# include "Menu/0.hpp"
# include "Menu/1.hpp"
# include "Menu/2.hpp"
# include "Menu/3.hpp"

# include "Test/Scroll.hpp"
# include "Test/List.hpp"

# include "UIManager.hpp"

struct UserInterfaceContext : public ContextBase
{
	UI::Manager				UIManager;
	
	UserInterfaceMenu0		Menu0;
	UserInterfaceMenu1		Menu1;
	UserInterfaceMenu2		Menu2;
	UserInterfaceMenu3		Menu3;
	::TestScroll	TestScroll;
	::TestList		TestList;

	~UserInterfaceContext();
	UserInterfaceContext();
	
	void	Make();
	void	ToggleMenu1(ClickArgs args);
	void	ToggleMenu2(ClickArgs args);
	void	ToggleMenu3(ClickArgs args);
	void	ToggleTestScroll(ClickArgs args);
	void	ToggleTestList(ClickArgs args);
	
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