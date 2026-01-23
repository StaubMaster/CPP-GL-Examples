#ifndef  UI_CONTROL_CHECKBOX_HPP
# define UI_CONTROL_CHECKBOX_HPP

#include "Base/Base.hpp"



namespace UI
{

namespace Control
{

class CheckBox : public Base
{
	public:
	void (*ClickFunc)(UserParameter::Mouse::Click params);

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
	void RelayClick(UserParameter::Mouse::Click params) override;
};

};

};

#endif