#include "Layout/Multiform/Display.hpp"



LayoutMultiformDisplay::LayoutMultiformDisplay()
	: ::Multiform::Layout()
	, DisplaySize("DisplaySize")
{
	Multiforms.Insert(&DisplaySize);
}
