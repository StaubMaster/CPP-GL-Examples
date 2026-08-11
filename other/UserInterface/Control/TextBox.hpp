#ifndef  UI_CONTROL_TEXTBOX_HPP
# define UI_CONTROL_TEXTBOX_HPP

# include "Control/General/Base.hpp"

# include "Text/Object.hpp"

namespace UI
{
namespace Control
{
class TextBox : public Base
{
	public:
	bool	ReadOnly;
	bool	MultiLine;

	public:
	UI::Text::Alignment		AlignmentX;
	UI::Text::Alignment		AlignmentY;

	public:
	~TextBox();
	TextBox();

	protected:
	void	RelayAssignDepth() override;
	public:
	void	BoxUpdate() override;
	void	ObjectInsert() override;
	void	ObjectRemove() override;

	public:
	void	RelayKey(KeyArgs args) override;
	void	RelayText(TextArgs args) override;

	private:
	Text::Object	TextObject;
	void			PutCharactersEntrys();
	public:
	void			PutAlignment();
	private:
	unsigned int	TextCursor;
	void			PutCursor();

	private:
	std::string		Text;
	public:
	std::string		GetText() const;
	void			SetText(std::string text);
};
};
};

#endif