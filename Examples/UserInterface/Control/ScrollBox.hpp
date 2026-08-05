#ifndef  SCROLL_BOX_HPP
# define SCROLL_BOX_HPP

# include "ControlsInclude.hpp"

class ScrollBox : public UI::Control::Base
{
	public:
	UI::Control::Base		Content;
	float					ContentSize;
	UI::Control::Slider		ScrollBar;

	public:
	~ScrollBox();
	ScrollBox();

	public:
	void	RelayBoxUpdate() override;

	public:
	/* CalcScroll
		this should be automatically called
		when Box changes. after Children have been updated
	*/
	void	CalcScroll();
	void	ScrollFunc(float val);
};

#endif