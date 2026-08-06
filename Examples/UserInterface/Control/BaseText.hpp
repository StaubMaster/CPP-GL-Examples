#ifndef  UI_CONTROL_BASE_TEXT_HPP
# define UI_CONTROL_BASE_TEXT_HPP

# include "Control/General/Base.hpp"

# include "Text/Object.hpp"

namespace UI
{
namespace Control
{
class BaseText : public Base
{
	public:
	virtual ~BaseText();
	BaseText();

	BaseText(const BaseText & other) = delete;
	BaseText & operator=(const BaseText & other) = delete;



	private:
	std::string		Text;
	public:
	std::string		GetText() const;
	void			SetText(std::string text);

	private:
	Text::Object	TextObject;
	bool			TextObjectNewText;
	bool			TextObjectNewBound;

	private:
	void	TextObjectAssign();
	void	TextObjectAssignText();
	void	TextObjectAssignBound();



	public:
	void	RelayBoxUpdate() override;
	void	RelayObjectInsert() override;
	void	RelayObjectRemove() override;
};
};
};

#endif