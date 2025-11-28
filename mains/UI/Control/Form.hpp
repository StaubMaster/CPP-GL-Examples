#ifndef  CONTROL_FORM_HPP
# define CONTROL_FORM_HPP

#include "Base/Base.hpp"



namespace Control
{
class Form : public Base
{
	public:
		Form(Manager & manager);
		~Form();
};
};

#endif