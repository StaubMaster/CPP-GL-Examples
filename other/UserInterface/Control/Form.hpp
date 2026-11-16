#ifndef  UI_CONTROL_FORM_HPP
# define UI_CONTROL_FORM_HPP

# include "Control/Control.hpp"

/* ControlBar
	X Button in Top Right to "close" Form
	the Top Bar in general is used to move
		currently any part of the Form, except those used for resizing, are used for moving

	make Optional ?
	area for Children should not include Bar
	BoxBoarder is different not default
	BoxContent is determined calculated from BoxBoarder
	override BoxUpdate
*/

/* make Form a Control (again)
*/

namespace UI
{
class Manager;
namespace Control_
{
class Window;
class Base;
class Form : public Control
{
	public:
	UI::Control_::Window *	Window_ = nullptr;

	public:
			UI::Manager *			_Manager() override;
			UI::Manager *			_Manager() const override;
			UI::Control_::Window *	_Window() override;
	const	UI::Control_::Window *	_Window() const override;
			UI::Control_::Form *	_Form() override;
	const	UI::Control_::Form *	_Form() const override;

	private: public:	float	DepthOffset_ = 0.0f;
	public:		void	DepthChange(float depth);
	public:		float	DepthOffset() const;



	public:
	virtual ~Form() = default;
	Form();

	public:
	bool	IsMovable = false;
	bool	IsResizable = false;
	//BoxF2	SizeLimit;



	private:
	enum class EBoxChangeType : unsigned char
	{
		None,
		Move,
		ResizeMinX,
		ResizeMaxX,
		ResizeMinY,
		ResizeMaxY,
		ResizeMinMin,
		ResizeMinMax,
		ResizeMaxMin,
		ResizeMaxMax,
	};

	private:
	EBoxChangeType	FindChangingArea(VectorF2 mouse) const;
	EBoxChangeType	ChangingBoxType;
	BoxF2			ChangingBoxRel;

	private:
	void	ChangeAnchorBox(BoxF2 box, EBoxChangeType type);

	public:
	void	RelayHover(HoverArgs args) override;
	void	RelayDrag(DragArgs args) override;
};
};
};

#endif