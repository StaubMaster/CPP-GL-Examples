#ifndef  CONTROL_WINDOW
# define CONTROL_WINDOW

#include "Base/Base.hpp"



namespace Control
{
class Window : public Base
{
	public:
		Window(Manager & manager);
		~Window();
};
};

#endif