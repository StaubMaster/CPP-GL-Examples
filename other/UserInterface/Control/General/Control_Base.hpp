#ifndef  UI_CONTROL_CONTROL_BASE_HPP
# define UI_CONTROL_CONTROL_BASE_HPP

# include "Control_Display.hpp"
# include "Control_UserRelay.hpp"
# include "Control_Container.hpp"

namespace UI
{
class Control_Base : public Control_Container, public Control_Display, public Control_UserRelay
{
	public:
	virtual			UI::Manager *			_Manager() = 0;
	virtual			UI::Manager *			_Manager() const = 0;
	virtual			UI::Control_::Window *	_Window() = 0;
	virtual	const	UI::Control_::Window *	_Window() const = 0;

	protected:	Control_Base *	Parent_ = nullptr;
	public:		Control_Base *	Parent() const;

	public:
	virtual void	ChildClear() override;
	virtual void	ChildRemove(Control_Base & control) override;
	virtual void	ChildInsert(Control_Base & control) override;

	public:
	bool					Check(const DisplayPosition & display_pos) const override;
	UI::Control_Base *		Find(const DisplayPosition & display_pos) override;

	public:	virtual	float	LayerDepth() const = 0;
	public:	virtual	float	DepthOffset() const = 0;

	public:
	virtual ~Control_Base() = default;
	Control_Base() = default;
	Control_Base(const Control_Base & other) = delete;
	Control_Base & operator=(const Control_Base & other) = delete;
};
};

#endif