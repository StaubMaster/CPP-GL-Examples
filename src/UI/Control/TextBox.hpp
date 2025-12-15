#ifndef  UI_CONTROL_TEXTBOX_HPP
# define UI_CONTROL_TEXTBOX_HPP

#include "Base/Base.hpp"
#include "../Text/Data.hpp"
#include "../Text/Manager.hpp"

#include "Miscellaneous/EntryContainer/Entry.hpp"

#include <string>



namespace UI
{

namespace Control
{

class TextBox : public Base
{
	private:
	UI::Text::Manager & TextManager;
	EntryContainer::Entry<UI::Text::Inst_Data> TextEntry;

	Point2D			CharacterSize;
	Point2D			CharacterCountLimit2D;
	unsigned int	CharacterCountLimit;
	bool			CharacterCountLimitChanged;

	std::string	Text;
	bool		TextChanged;

	public:
	bool	ReadOnly;
	bool	SingleLine;

	public:
	TextBox(UI::Text::Manager & text_manager);
	~TextBox();

	private:
	void ShowInfo() const;

	private:
	void CalcCharacterCount();
	void PutCharactersEntrys();

	public:
	std::string GetText() const;
	void SetText(std::string text);

	public:
	void UpdateEntrysRelay() override;
	void InsertDrawingEntryRelay() override;
	void RemoveDrawingEntryRelay() override;
	void UpdateBoxRelay() override;

	public:
	void RelayKey(UserParameter::KeyBoard::Key params) override;
	void RelayText(UserParameter::KeyBoard::Text params) override;
};

};

};

#endif