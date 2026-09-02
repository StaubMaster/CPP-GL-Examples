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
namespace Control
{
class Form : public Base
{
	public:
	void	ChildInsert(Base & control) override;
	void	ChildRemove(Base & control) override;
	void	ChildClear() override;

	public:
	virtual ~Form();
	Form();

	public:
	bool	IsMovable;
	bool	IsResizable;
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