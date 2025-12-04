#ifndef  UI_CONTROL_FORM_HPP
# define UI_CONTROL_FORM_HPP

#include "Base/Base.hpp"



namespace UI
{

namespace Control
{

class Form : public Base
{
	public:
		Form(Manager & manager);
		~Form();
};

};

};

#endif