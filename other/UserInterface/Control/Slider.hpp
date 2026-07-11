#ifndef  UI_CONTROL_SLIDER_HPP
# define UI_CONTROL_SLIDER_HPP

# include "Control/General/Base.hpp"

# include "Generics/Function/Pointer.hpp"

# include "Text/Object.hpp"

namespace UI
{

namespace Control
{

class Slider : public Base
{
	private:
	Object		SliderObject;
	// Area Slider naturally creates a "dot"
	// make a Cross instead ?
	// meaning different Slider Objects for Vert and Hori ?
	// dont display the unused one, since it would cover the whole Control

	private:
	bool		SliderChanged;
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

	public:
	VectorF2	GetValue() const;
	float		GetValueX() const;
	float		GetValueY() const;
	void		SetValue(VectorF2 val);
	void		SetValueX(float val);
	void		SetValueY(float val);

	private:
	void	PutSliderNub();
	void	ClampValue();

	private:
	void ChangeValue(DisplayPosition mouse_pos);

	public:
	FunctionPointer<float>		ValueXChangedFunc;
	FunctionPointer<float>		ValueYChangedFunc;
	FunctionPointer<VectorF2>	ValueChangedFunc;

	public:
	Slider();
	~Slider();

	public:
	void	RelayUpdateBox() override;
	void	RelayInsertObject() override;
	void	RelayRemoveObject() override;

	void	RelayClick(ClickArgs params) override;
	void	RelayCursorDrag(DragArgs params) override;
	void	RelayKey(KeyArgs args) override;

	private:
	Text::Object	TextObject;
	std::string		Text;
	private:
	void	PutCharactersEntrys();
	public:
	std::string		GetText() const;
	void			SetText(std::string text);
};

};

};

#endif