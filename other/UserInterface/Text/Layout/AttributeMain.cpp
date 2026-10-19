#include "Text/Layout/AttributeMain.hpp"
#include "Text/DataMain.hpp"



UI::Text::LayoutAttributeMain::LayoutAttributeMain()
	: ::Attribute::Layout(0, sizeof(DataMain))
	, Pos(*this)
{ }
