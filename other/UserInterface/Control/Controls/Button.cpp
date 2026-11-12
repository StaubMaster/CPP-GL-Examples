#include "Control/Controls/Button.hpp"
#include "AnchorEnum.hpp"
#include "User/MouseArgs.hpp"
#include "Text/Manager.hpp"
#include <math.h>



UI::Control::Button::Button()
	: BaseText()
{
	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
	AnchorSize = VectorF2(75, 16);

	float padding = 0;
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));

	ColorDefault = ColorF4(0.625f, 0.625f, 0.625f);
	ColorHover = ColorF4(0.5f, 0.5f, 0.5f);

	AlignmentX = UI::Text::Alignment::Mid;
	AlignmentY = UI::Text::Alignment::Mid;

}



void UI::Control::Button::RelayClick(ClickArgs params)
{
	if (!IsInteractible()) { return; }

	ClickFunc.TryInvoke(params);
}
