#ifndef  UI_CONTROL_BUTTON_HPP
# define UI_CONTROL_BUTTON_HPP

# include "Base/Base.hpp"
# include "Miscellaneous/Function/Pointer.hpp"

# include "../Text/Object.hpp"
# include <string>

namespace UI
{

namespace Control
{

class Button : public Base
{
	public:
	FunctionPointer<ClickArgs>	ClickFunc;

	public:
	~Button();
	Button();

	public:
//	void	UpdateEntrysRelay() override;
	void	InsertDrawingEntryRelay() override;
	void	RemoveDrawingEntryRelay() override;
	void	UpdateBoxRelay() override;

	public:
	void	RelayClick(ClickArgs args) override;

	private:
	Text::Object	TextObject;
	void			PutCharactersEntrys();
	private:
	std::string		Text;
	public:
	std::string	GetText() const;
	void		SetText(std::string text);
};

};

};

#endif