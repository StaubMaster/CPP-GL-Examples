#ifndef  SELECTOR_CONTEXT_MENU_HPP
# define SELECTOR_CONTEXT_MENU_HPP

# include "ControlsInclude.hpp"

struct SelectorMenu : public UI::Control::Form
{
	UI::Control::Button		QuitButton;
	UI::Control::Label		TitleText;

	UI::Control::Button		SelectorButton;
	UI::Control::Button		UserInterfaceButton;
	UI::Control::Button		NoisePlaneButton;
	UI::Control::Button		Light3D;

	UI::Control::Graph		TEST_GRAPH;

	~SelectorMenu();
	SelectorMenu();

	void	QuitFunc(ClickArgs args);
	void	SelectorFunc(ClickArgs args);
	void	UserInterfaceFunc(ClickArgs args);
	void	NoisePlaneFunc(ClickArgs args);
	void	Light3DFunc(ClickArgs args);
};

#endif