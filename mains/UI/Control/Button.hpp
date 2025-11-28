#ifndef  CONTROL_BUTTON_HPP
# define CONTROL_BUTTON_HPP

#include "Base/Base.hpp"



namespace Control
{
class Button : public Base
{
public:
	Button(Manager & manager);
	~Button();
};
};

#endif