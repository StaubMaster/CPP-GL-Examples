#ifndef  UI_CONTROL_SLIDER_HPP
# define UI_CONTROL_SLIDER_HPP

#include "Base/Base.hpp"



namespace UI
{

namespace Control
{

/*
	go from min to max
	slider position depends on slider size ?
*/

class Slider : public Base
{
	private:
	EntryContainer::Entry<Control::Inst_Data> SliderEntry;

	bool SliderChanged;
	float SliderSize;

	float SliderValue;
	public:
	float SliderMin;
	float SliderMax;

	public:
	void (*ValueChangedFunc)(float);

	public:
	Slider(Manager & manager);
	~Slider();

	public:
	float GetValue();
	void SetValue(float val);

	public:
	void UpdateEntrysRelay() override;
	void UpdateVisibilityRelay(bool make_visible) override;
	void UpdateBoxRelay() override;

	void RelayClick(UI::Parameter::Click params) override;
};

};

};

#endif