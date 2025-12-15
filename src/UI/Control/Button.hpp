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
	void (*ClickFunc)(UserParameter::Mouse::Click params);

	public:
	Button();
	~Button();

	public:
	void RelayClick(UserParameter::Mouse::Click params) override;
};

};

};

#endif