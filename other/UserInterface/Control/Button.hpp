#ifndef  UI_CONTROL_BUTTON_HPP
# define UI_CONTROL_BUTTON_HPP

# include "Base/Base.hpp"
# include "Miscellaneous/Function/Pointer.hpp"

# include "../Text/Object.hpp"

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
	void	RelayUpdateBox() override;
	void	RelayInsertObject() override;
	void	RelayRemoveObject() override;

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