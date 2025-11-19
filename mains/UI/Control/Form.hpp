#ifndef  CONTROL_FORM
# define CONTROL_FORM

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