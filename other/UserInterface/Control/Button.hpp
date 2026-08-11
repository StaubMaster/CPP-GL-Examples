#ifndef  UI_CONTROL_BUTTON_HPP
# define UI_CONTROL_BUTTON_HPP

# include "Control/General/BaseText.hpp"

# include "Generics/Function/Pointer.hpp"

# include "Text/Object.hpp"

namespace UI
{

namespace Control
{

class Button : public BaseText
{
	public:
	FunctionPointer<ClickArgs>	ClickFunc;

	public:
	~Button();
	Button();

	private:
	void	TextObjectAssignPosition() override;

	public:
	void	RelayClick(ClickArgs args) override;
};

};

};

#endif