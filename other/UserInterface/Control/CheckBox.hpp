#ifndef  UI_CONTROL_CHECKBOX_HPP
# define UI_CONTROL_CHECKBOX_HPP

# include "Base/Base.hpp"
# include "Miscellaneous/Function/Pointer.hpp"



namespace UI
{

namespace Control
{

class CheckBox : public Base
{
	public:
	FunctionPointer<ClickArgs>	ClickFunc;

	private:
	bool Checked;

	private:
	ColorF4 ColorChecked;
	ColorF4 ColorCheckedHover;
	bool Color2Changed;

	public:
	CheckBox();
	~CheckBox();

	public:
	bool IsChecked();
	void Toggle();
	void Check(bool state);

	protected:
	void UpdateEntryColorRelay() override;
	void RelayHover(unsigned char type) override;

	public:
	void RelayClick(ClickArgs params) override;
};

};

};

#endif