#ifndef  UI_CONTROL_FORM_HPP
# define UI_CONTROL_FORM_HPP

#include "Base/Base.hpp"


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
		Form();
		~Form();
};

};

};

#endif