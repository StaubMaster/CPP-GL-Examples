#ifndef  UI_CONTROL_FORM_HPP
# define UI_CONTROL_FORM_HPP

# include "Control/General/Base.hpp"

/*	TODO
dont overlap with other Forms
	eighter completely behind another or infront of another
	have a seperate draw call for each form ?
movable
	bool isMovable
resizable
	like window,
	bool resizableX
	bool resizableY
*/

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

namespace UI
{
class Manager;
namespace Control
{
class Window;
class Form : public Base
{
	public:
	UI::Control::Window *	Window_ = nullptr;

	public:
			UI::Manager *			_Manager() override;
			UI::Manager *			_Manager() const override;
			UI::Control::Window *	_Window() override;
	const	UI::Control::Window *	_Window() const override;
			UI::Control::Form *		_Form() override;
	const	UI::Control::Form *		_Form() const override;

	public:
	void	AssignPointers(Base & control) override;



	protected:
	void	AnchorUpdate() override;

	public:
	BoxF2	BoxDisplay() const override;
	BoxF2	BoxBoarder() const override;
	BoxF2	BoxContent() const override;



	public:
	virtual ~Form() = default;
	Form();

	public:
	float	DepthOffset = 0.0f;

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