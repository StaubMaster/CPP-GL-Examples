#include "Layout/Uniform/Display.hpp"



LayoutUniformDisplay::LayoutUniformDisplay()
	: ::Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
{ }
