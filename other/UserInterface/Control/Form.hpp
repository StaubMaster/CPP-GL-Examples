#ifndef  UI_CONTROL_FORM_HPP
# define UI_CONTROL_FORM_HPP

# include "Base/Base.hpp"

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
	enum class EChangingBoxType : unsigned char
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
	EChangingBoxType	FindChangingArea(VectorF2 mouse) const;

	EChangingBoxType	ChangingBoxType;
	BoxF2				ChangingBoxRel;

	public:
	void	RelayHover(HoverArgs args) override;
	void	RelayCursorDrag(DragArgs args) override;
};

};

};

#endif