#include "Control/Controls/Label.hpp"
#include "Control/General/Manager.hpp"
#include "AnchorEnum.hpp"

#include "Text/Manager.hpp"
#include <math.h>



UI::Control::Label::Label()
	: BaseText()
{
	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
	AnchorSize = VectorF2(50, 20);

	float padding = 0;
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));

	ColorDefault = ColorF4(0.75f, 0.75f, 0.75f);
	ColorHover = ColorF4(0.75f, 0.75f, 0.75f);

	AlignmentX = UI::Text::Alignment::Min;
	AlignmentY = UI::Text::Alignment::Min;
}
