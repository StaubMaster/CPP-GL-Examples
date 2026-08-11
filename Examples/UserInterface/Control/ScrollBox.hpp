#ifndef  UI_CONTROL_SCROLL_BOX_HPP
# define UI_CONTROL_SCROLL_BOX_HPP

# include "Control/General/Base.hpp"
# include "Control/Slider.hpp"

namespace UI
{
namespace Control
{
class ScrollBox : public Base
{
	public:
	Base		Content;
	float		ContentSize;
	Slider		ScrollBar;

	public:
	~ScrollBox();
	ScrollBox();

	public:
	void	BoxUpdate() override;

	public:
	/* CalcScroll
		this should be automatically called
		when Box changes. after Children have been updated
	*/
	void	CalcScroll();
	void	ScrollFunc(float val);

	public:
	/*
		this only works if this control is being hovered
		it should if this or any child is being hovered
		and non of the children absorb the scroll themselves

		when scrolling (any user relay ?)
		return a bool. true if absorben, false if not
		give scroll args to hovering
		if not absorbed, give to parent
		loop until absorbed or no parent
	*/
	void	RelayScroll(ScrollArgs args) override;
};
};
};

#endif