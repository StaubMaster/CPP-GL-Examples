#ifndef  UI_CONTROL_SLIDER_HPP
# define UI_CONTROL_SLIDER_HPP

# include "Base/Base.hpp"
# include "Miscellaneous/Function/Pointer.hpp"



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
	float SliderSize;	//NubSize

	float Value;
	public:
	float ValueResolution;
	float ValueMin;
	float ValueMax;

	public:
	//void (*ValueChangedFunc)(float);
	FunctionPointer<float>	ValueChangedFunc;

	public:
	Slider();
	~Slider();

	public:
	float GetValue();
	void SetValue(float val);
	private:
	void ChangeValue(DisplayPosition mouse_pos);

	public:
	void UpdateEntrysRelay() override;
	void InsertDrawingEntryRelay() override;
	void RemoveDrawingEntryRelay() override;
	void UpdateBoxRelay() override;

	void RelayClick(ClickArgs params) override;
	void RelayCursorDrag(DragArgs params) override;
};

};

};

#endif