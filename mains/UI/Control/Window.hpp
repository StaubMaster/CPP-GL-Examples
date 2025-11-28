#ifndef  CONTROL_WINDOW_HPP
# define CONTROL_WINDOW_HPP

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