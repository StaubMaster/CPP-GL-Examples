#include "InstLayout.hpp"
#include "InstData.hpp"



UI::Control::Inst::Layout::Layout()
	: ::Attribute::Layout(1, sizeof(Inst::Data))
	, Box(*this)
	, Layer(*this)
	, Color(*this)
	, Bound(*this)
{ }
