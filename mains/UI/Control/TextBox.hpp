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
	bool ChangedText;
	std::string String;
	EntryContainer::Entry<UI::Text::Inst_Data> TextEntry;

	public:
	bool ReadOnly;
	bool SingleLine;

	public:
	TextBox(Manager & control_manager, UI::Text::Manager & text_manager);
	~TextBox();

	public:
	std::string GetText() const;
	void SetText(std::string str);

	public:
	void UpdateEntrysRelay() override;
	void UpdateVisibilityRelay(bool make_visible) override;
	void UpdateBoxRelay() override;

/*
Estimate how many Characters can fit in the TextBox
allocate an Entry with that much
when UpdatingTextString, only set the ones in the Text Box

have a way to cull Text outside of the Box (done in Shader)
*/

public:
	void RelayKey(UI::Parameter::Key params) override;
	void RelayText(UI::Parameter::Text params) override;
};

};

};

#endif