#ifndef  UI_CONTROL_TEXTBOX_HPP
# define UI_CONTROL_TEXTBOX_HPP

#include "Base/Base.hpp"

#include "../Text/Object.hpp"
#include <string>

namespace UI
{
namespace Control
{
class TextBox : public Base
{
	private:
	Text::Object	TextObject;

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
	TextBox();
	~TextBox();

	private:
	void	ShowInfo() const;

	private:
	void	CalcCharacterCount();
	void	PutCharactersEntrys();

	public:
	std::string	GetText() const;
	void		SetText(std::string text);

	public:
	void	UpdateEntrysRelay() override;
	void	InsertDrawingEntryRelay() override;
	void	RemoveDrawingEntryRelay() override;
	void	UpdateBoxRelay() override;

	public:
	void	RelayKey(KeyArgs params) override;
	void	RelayText(TextArgs params) override;
};
};
};

#endif