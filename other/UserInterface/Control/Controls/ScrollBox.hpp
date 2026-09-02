#ifndef  UI_CONTROL_SCROLL_BOX_HPP
# define UI_CONTROL_SCROLL_BOX_HPP

# include "Control/General/Base.hpp"
# include "Control/Controls/Slider.hpp"

namespace UI
{
namespace Control
{
class ScrollBox;
class ScrollContent : public Base
{
	public:
	ScrollBox &		Box;

	public:
	float	CalcRatio(float & control_range_size, float & content_size);

	public:
	~ScrollContent();
	ScrollContent(ScrollBox & box);

	public:
	void	BoxUpdate() override;

	public:
	void	AutoAnchorUpdate() override;
};
class ScrollBox : public Base
{
	private: public:
	ScrollContent	Content;
	Slider			ScrollBar;

	public:
	~ScrollBox();
	ScrollBox();

	public:
	void	ChildInsert(Base & control) override;
	void	ChildRemove(Base & control) override;
	void	ChildClear() override;

	public:
	void	BoxUpdate() override;

	public:
	/* CalcScroll
		this should be automatically called when ...
			Box changes
			Child Box changes
			Child Visibility changes
		Content uses AutoAnchor
		so it automatically changes Box when...
			Child Box changes
			Child Visibility changes
		so this only has to catch when ...
			Box changes

		Box change should automatically request AutoAnchor change from Parent
		so this should be able to override AutoAnchorUpdate
	*/
	void	ScrollNone();
	void	ScrollCalc();
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