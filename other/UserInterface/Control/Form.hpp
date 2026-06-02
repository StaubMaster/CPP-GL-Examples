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

	private:
	bool	IsMoving;
	BoxF2	MovingRel;
	void	UserMoving(DragArgs args);


	public:
	bool	IsResizableX;
	bool	IsResizableY;
	//BoxF2	SizeLimit;

	private:
	bool			IsResizing;
	unsigned char	Boarder;
	BoxF2			BoarderRel;
	void			UserResize(DragArgs args);

	public:
	void	RelayCursorDrag(DragArgs args) override;
};

};

};

#endif