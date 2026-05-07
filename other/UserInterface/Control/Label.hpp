#ifndef  UI_CONTROL_LABEL_HPP
# define UI_CONTROL_LABEL_HPP

#include "Base/Base.hpp"

#include "../Text/Object.hpp"
#include <string>

namespace UI
{
namespace Control
{
class Label : public Base
{
	public:
	~Label();
	Label();

	public:
//	void	UpdateEntrysRelay() override;
	void	InsertDrawingEntryRelay() override;
	void	RemoveDrawingEntryRelay() override;
	void	UpdateBoxRelay() override;

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