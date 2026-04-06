#ifndef  UI_CONTROL_BUTTON_HPP
# define UI_CONTROL_BUTTON_HPP

# include "Base/Base.hpp"
# include "Miscellaneous/Function/Pointer.hpp"



namespace UI
{

namespace Control
{

class Button : public Base
{
	public:
	FunctionPointer<ClickArgs>	ClickFunc;

	public:
	Button();
	~Button();

	public:
	void RelayClick(ClickArgs args) override;
};

};

};

#endif