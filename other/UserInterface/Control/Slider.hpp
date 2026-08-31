#ifndef  UI_CONTROL_SLIDER_HPP
# define UI_CONTROL_SLIDER_HPP

# include "Control/General/BaseText.hpp"

# include "Generics/Function/Pointer.hpp"

namespace UI
{
namespace Control
{
class Slider : public BaseText
{
	private:
	Control::Object		SliderObject;
	/* Area Slider
		naturally creates a "dot"
		make a Cross instead ?
		meaning different Slider Objects for Vert and Hori ?
		dont display the unused one, since it would cover the whole Control
	*/

	private:
	bool		SliderChanged; // request/resolve ?
	public:
	VectorF2	NubSize;

	private:
	VectorF2	Value;
	public:
	VectorF2	ValueResolution;
	// make this a Box
	VectorF2	ValueMin;
	VectorF2	ValueMax;
	// Get/Set for these
	// ValueScrollChange ? how much does the value change from Scrolling

	public:
	VectorF2	GetValue() const;
	float		GetValueX() const;
	float		GetValueY() const;
	void		SetValue(VectorF2 val);
	void		SetValueX(float val);
	void		SetValueY(float val);

	private:
	public: // temp
	void	PutSliderNub();
	void	ClampValue();

	private:
	void	ChangeValue(DisplayPosition mouse_pos);

	public:
	FunctionPointer<float>		ValueXChangedFunc;
	FunctionPointer<float>		ValueYChangedFunc;
	FunctionPointer<VectorF2>	ValueChangedFunc;

	public:
	Slider();
	~Slider();

	protected:
	void	RelayAssignDepth() override;
	public:
	void	BoxUpdate() override;
	void	DisplayShow() override;
	void	DisplayHide() override;
	
	public:
	void	RelayClick(ClickArgs args) override;
	void	RelayDrag(DragArgs args) override;
	void	RelayKey(KeyArgs args) override;
	// Scroll
};
};
};

#endif