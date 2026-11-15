#ifndef  UI_CONTROL_CONTROL_BASE_HPP
# define UI_CONTROL_CONTROL_BASE_HPP

# include "Control_Display.hpp"
# include "Control_UserRelay.hpp"
# include "Control_Container.hpp"

namespace UI
{
class Control_Base : public Control_Container<Control_Base>, public Control_Display, public Control_UserRelay
{
	protected:	Control_Base *	Parent_ = nullptr;
	public:		Control_Base *	Parent() const;

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