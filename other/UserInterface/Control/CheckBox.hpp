#ifndef  UI_CONTROL_CHECKBOX_HPP
# define UI_CONTROL_CHECKBOX_HPP

# include "Base/Base.hpp"
# include "Generics/Function/Pointer.hpp"



namespace UI
{

namespace Control
{

class CheckBox : public Base
{
	public:
	FunctionPointer<ClickArgs>	ClickFunc;

	private:
	bool	Checked;

	private:
	ColorF4		ColorChecked;
	ColorF4		ColorCheckedHover;

	public:
	CheckBox();
	~CheckBox();

	public:
	bool	IsChecked();
	void	Toggle();
	void	Check(bool state);

	protected:
	void	RelayAssignObjectColor() override;
	void	RelayHover(HoverArgs args) override;

	public:
	void	RelayClick(ClickArgs params) override;
};

};

};

#endif