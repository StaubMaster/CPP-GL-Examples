#include "Layout.hpp"
#include "Data.hpp"



UI::Text::Inst::Layout::Layout()
	: ::Attribute::Layout(1, sizeof(Data))
	, TextPos(*this)
	, CharIdx(*this)
	, TextIdx(*this)
{ }
