#ifndef  UI_CONTROL_SLIDER_HPP
# define UI_CONTROL_SLIDER_HPP

# include "Base/Base.hpp"
# include "UI/CallBack/Base.hpp"



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
	//void (*ValueChangedFunc)(float);
	BaseCallBack<float> * ValueChangedFunc;

	public:
	Slider();
	~Slider();

	public:
	float GetValue();
	void SetValue(float val);

	public:
	void UpdateEntrysRelay() override;
	void InsertDrawingEntryRelay() override;
	void RemoveDrawingEntryRelay() override;
	void UpdateBoxRelay() override;

	void RelayClick(UserParameter::Mouse::Click params) override;
	void RelayCursorDrag(UserParameter::Mouse::Drag params) override;
};

};

};

#endif