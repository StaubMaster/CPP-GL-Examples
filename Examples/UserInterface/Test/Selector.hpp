#ifndef  USER_INTERFACE_TEST_SELECTOR_HPP
# define USER_INTERFACE_TEST_SELECTOR_HPP

# include "Control/_Include.hpp"

struct TestSelector : public UI::Control_::Form
{
	UI::Control_::Label		TitleText;
	UI::Control_::Button	QuitButton;
	UI::Control_::Button	ReButton;

	UI::Control_::Button	TileGridButton;
	UI::Control_::Button	TextButton;
	UI::Control_::Button	GraphButton;
	UI::Control_::Button	TestScrollButton;
	UI::Control_::Button	TestListButton;
	UI::Control_::Button	DirectoryNavigatorButton;

	TestSelector();

	void	QuitFunc(ClickArgs args);
	void	ReFunc(ClickArgs args);
	void	BackFunc(ClickArgs args);
};

#endif