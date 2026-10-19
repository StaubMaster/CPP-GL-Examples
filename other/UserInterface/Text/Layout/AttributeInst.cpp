#include "Text/Layout/AttributeInst.hpp"
#include "Text/DataInst.hpp"



UI::Text::LayoutAttributeInst::LayoutAttributeInst()
	: ::Attribute::Layout(1, sizeof(DataInst))
	, TextPos(*this)
	, CharIdx(*this)
	, TextIdx(*this)
{ }
