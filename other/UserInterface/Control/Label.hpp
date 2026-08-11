#ifndef  UI_CONTROL_LABEL_HPP
# define UI_CONTROL_LABEL_HPP

# include "Control/General/BaseText.hpp"

#include "Text/Object.hpp"

namespace UI
{
namespace Control
{
class Label : public BaseText
{
	public:
	~Label();
	Label();

	private:
	void	TextObjectAssignPosition() override;
};
};
};

#endif