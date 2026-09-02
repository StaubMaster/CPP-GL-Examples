#ifndef  UI_CONTROL_BUTTON_HPP
# define UI_CONTROL_BUTTON_HPP

# include "Control/General/BaseText.hpp"

# include "Generics/Function/Pointer.hpp"

namespace UI
{
namespace Control
{
class Button : public BaseText
{
	public:
	FunctionPointer<ClickArgs>	ClickFunc; // FuncClick

	public:
	~Button();
	Button();

	private:
	void	TextObjectAssignPosition() override;

	public: // does this need to be public ?
	void	RelayClick(ClickArgs args) override;
};
};
};

#endif