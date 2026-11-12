#ifndef  UI_CONTROL_SLIDER_HPP
# define UI_CONTROL_SLIDER_HPP

# include "Control/General/BaseText.hpp"

# include "Generics/Function/Pointer.hpp"

//# include "Object.hpp"
//# include "ObjectData.hpp"

namespace UI
{
namespace Control
{
class Slider : public BaseText
{
	private:	VectorF2	Value;
	public:		BoxF2		ValueRange;
	public:		VectorF2	ValueResolution;
	// Get/Set for these
	// ValueScrollChange ? how much does the value change from Scrolling

	private:
	void	ClampValue();

	public:
	VectorF2	GetValue() const;
	float		GetValueX() const;
	float		GetValueY() const;
	public:
	void		SetValue(VectorF2 val);
	void		SetValueX(float val);
	void		SetValueY(float val);

	private:
	void	ChangeValue(DisplayPosition mouse_pos);



	public:
	VectorF2	NubSize;
	private:
	BoxF2		NubBox;

	private:
	bool		NubObject_Display = false;
	/* Area Slider
		naturally creates a "dot"
		make a Cross instead ?
		meaning different Slider Objects for Vert and Hori ?
		dont display the unused one, since it would cover the whole Control
	*/

	private:	bool	NubUpdateRequested = false;
	public:		void	NubUpdateRequest();
	private:	void	NubUpdate();



	public:
	Function::Pointer<float>		ValueXChangedFunc;
	Function::Pointer<float>		ValueYChangedFunc;
	Function::Pointer<VectorF2>		ValueChangedFunc;

	public:
	Slider();

	protected:
	void	AnchorUpdate() override;
	void	Update() override;
	public:
	void	DisplayPut() const override;
	void	DisplayShow() override;
	void	DisplayHide() override;
	
	public:
	void	RelayClick(ClickArgs args) override;
	void	RelayDrag(DragArgs args) override;
	void	RelayKey(KeyArgs args) override;
	//void	RelayScroll(ScrollArgs args) override;
};
};
};

#endif