#ifndef  UI_CONTROL_BUTTON_HPP
# define UI_CONTROL_BUTTON_HPP

# include "Base/Base.hpp"
# include "Function/Pointer.hpp"



namespace UI
{

namespace Control
{

class Button : public Base
{
	public:
	FunctionPointer<UserParameter::Mouse::Click>	ClickFunc;

	public:
	Button();
	~Button();

	public:
	void RelayClick(UserParameter::Mouse::Click params) override;
};

};

};

#endif