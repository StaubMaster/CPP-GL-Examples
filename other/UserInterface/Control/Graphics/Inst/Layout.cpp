#include "Layout.hpp"
#include "Data.hpp"



UI::Control::Inst::Layout::Layout()
	: ::Attribute::Layout(1, sizeof(Data))
	, Box(*this)
	, Layer(*this)
	, Color(*this)
	, Bound(*this)
{ }
