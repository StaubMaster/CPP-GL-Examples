#ifndef  USER_INTERFACE_CONTEXT_HPP
# define USER_INTERFACE_CONTEXT_HPP

# include "ContextBase.hpp"

# include "Test/Selector.hpp"
# include "Test/TileGrid.hpp"
# include "Test/Text.hpp"
# include "Test/Graph.hpp"
# include "Test/Scroll.hpp"
# include "Test/List.hpp"

# include "Form/DirectoryNavigator.hpp"

# include "UIManager.hpp"

struct UserInterfaceContext : public ContextBase
{
	UI::Manager				UIManager;

	::TestSelector			Selector;
	::TestTileGrid			TileGrid;
	::TestText				Text;
	::TestGraph				Graph;
	::TestScroll			TestScroll;
	::TestList				TestList;
	::DirectoryNavigator	DirectoryNavigator;

	UserInterfaceContext();
	
	void	Make();
	void	ToggleTileGrid(ClickArgs args);
	void	ToggleText(ClickArgs args);
	void	ToggleGraph(ClickArgs args);
	void	ToggleTestScroll(ClickArgs args);
	void	ToggleTestList(ClickArgs args);
	void	ToggleDirectoryNavigator(ClickArgs args);
	
	void	Init() override;
	void	Free() override;
	
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