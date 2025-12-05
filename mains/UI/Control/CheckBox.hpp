#ifndef  UI_CONTROL_CHECKBOX_HPP
# define UI_CONTROL_CHECKBOX_HPP

#include "Base/Base.hpp"



namespace UI
{

namespace Control
{

class CheckBox : public Base
{
	private:
	bool Checked;

	private:
	Color ColorChecked;
	Color ColorCheckedHover;
	bool Color2Changed;

	public:
	CheckBox(Manager & manager);
	~CheckBox();

	public:
	bool IsChecked();
	void Toggle();
	void Check(bool state);

	protected:
	void UpdateEntryColorRelay() override;
	void RelayHover(unsigned char type) override;

	public:
	void RelayClick(UI::Parameter::Click params) override;
};

};

};

#endif