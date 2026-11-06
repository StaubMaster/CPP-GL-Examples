#ifndef  UI_CONTROL_TEXTBOX_HPP
# define UI_CONTROL_TEXTBOX_HPP

# include "Control/General/BaseText.hpp"

# include "Text/ObjectData.hpp"

namespace UI
{
namespace Control
{
class TextBox : public BaseText
{
	public:
	bool	ReadOnly = false;
	bool	MultiLine = false;

	public:
	TextBox();

	public:
	void	RelayKey(KeyArgs args) override;
	void	RelayText(TextArgs args) override;
};
};
};

#endif