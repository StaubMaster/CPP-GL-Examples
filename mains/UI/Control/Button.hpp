#ifndef  CONTROL_BUTTON
# define CONTROL_BUTTON

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