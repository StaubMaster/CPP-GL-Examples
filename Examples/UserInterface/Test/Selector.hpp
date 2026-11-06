#ifndef  USER_INTERFACE_TEST_SELECTOR_HPP
# define USER_INTERFACE_TEST_SELECTOR_HPP

# include "Control/_Include.hpp"

struct TestSelector : public UI::Control::Form
{
	UI::Control::Label		TitleText;
	UI::Control::Button		QuitButton;
	UI::Control::Button		ReButton;

	UI::Control::Button		TileGridButton;
	UI::Control::Button		TextButton;
	UI::Control::Button		GraphButton;
	UI::Control::Button		TestScrollButton;
	UI::Control::Button		TestListButton;
	UI::Control::Button		DirectoryNavigatorButton;

	TestSelector();

	void	QuitFunc(ClickArgs args);
	void	ReFunc(ClickArgs args);
	void	BackFunc(ClickArgs args);
};

#endif