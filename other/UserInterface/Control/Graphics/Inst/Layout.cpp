#include "Layout.hpp"
#include "Data.hpp"



UI::ControlGraphics::Inst::Layout::Layout()
	: ::Attribute::Layout(1, sizeof(Data))
	, Box(*this)
	, Layer(*this)
	, Color(*this)
	, Bound(*this)
{ }
