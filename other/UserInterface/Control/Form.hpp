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

namespace UI
{

namespace Control
{

class Form : public Base
{
	public:
	~Form();
	Form();



	public:
	bool	IsMovable;
	bool	IsResizable;
	//BoxF2	SizeLimit;

	private:
	EBoxChangeType	FindChangingArea(VectorF2 mouse) const;
	EBoxChangeType	ChangingBoxType;
	BoxF2			ChangingBoxRel;

	public:
	void	RelayHover(HoverArgs args) override;
	void	RelayCursorDrag(DragArgs args) override;
};

};

};

#endif