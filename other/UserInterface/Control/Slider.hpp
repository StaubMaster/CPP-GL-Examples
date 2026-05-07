#ifndef  UI_CONTROL_SLIDER_HPP
# define UI_CONTROL_SLIDER_HPP

# include "Base/Base.hpp"
# include "Miscellaneous/Function/Pointer.hpp"

# include "../Text/Object.hpp"
# include <string>

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
	void ChangeValue(DisplayPosition mouse_pos);

	public:
	FunctionPointer<float>		ValueXChangedFunc;
	FunctionPointer<float>		ValueYChangedFunc;
	FunctionPointer<VectorF2>	ValueChangedFunc;

	private:
	Text::Object	TextObject;
	Point2D			CharacterSize;
	Point2D			CharacterCountLimit2D;
	unsigned int	CharacterCountLimit;
	bool			CharacterCountLimitChanged;
	std::string		Text;
	bool			TextChanged;

	public:
	Slider();
	~Slider();

	private:
	void	CalcCharacterCount();
	void	PutCharactersEntrys();

	public:
	std::string		GetText() const;
	void			SetText(std::string text);

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