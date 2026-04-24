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

	bool SliderChanged;
	float SliderSize;	//NubSize

	float Value;
	public:
	float ValueResolution;
	float ValueMin;
	float ValueMax;

	private:
	Text::Object	TextObject;
	Point2D			CharacterSize;
	Point2D			CharacterCountLimit2D;
	unsigned int	CharacterCountLimit;
	bool			CharacterCountLimitChanged;
	std::string		Text;
	bool			TextChanged;

	public:
	FunctionPointer<float>	ValueChangedFunc;

	public:
	Slider();
	~Slider();

	public:
	float GetValue();
	void SetValue(float val);
	private:
	void ChangeValue(DisplayPosition mouse_pos);

	private:
	void	CalcCharacterCount();
	void	PutCharactersEntrys();

	public:
	std::string	GetText() const;
	void		SetText(std::string text);

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