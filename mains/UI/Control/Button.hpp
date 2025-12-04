#ifndef  UI_CONTROL_BUTTON_HPP
# define UI_CONTROL_BUTTON_HPP

#include "Base/Base.hpp"



namespace UI
{

namespace Control
{

class Button : public Base
{
public:
	Button(Manager & manager);
	~Button();
};

};

};

#endif