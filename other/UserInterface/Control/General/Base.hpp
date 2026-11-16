#ifndef  UI_CONTROL_BASE_HPP
# define UI_CONTROL_BASE_HPP

# include "Control_Base.hpp"

namespace UI
{
namespace Control_
{
// rename from Base to Control
// put outside of Control namespace
class Base : public Control_Base
{
	protected:
			UI::Manager *			_Manager() override;
			UI::Manager *			_Manager() const override;
			UI::Control_::Window *	_Window() override;
	const	UI::Control_::Window *	_Window() const override;
	// these suck, find a way to replace them

	public:		float	LayerDepth() const override;
	public:		float	DepthOffset() const override;



	protected:
	bool	MetaIs() const override;
	BoxF2	MetaBoxBoarder() const override;
	BoxF2	MetaBoxContent() const override;



	public:
	virtual ~Base() = default;
	Base() = default;
	Base(const Base & other) = delete;
	Base & operator=(const Base & other) = delete;
};
};
};

#endif