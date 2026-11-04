#include "MainLayout.hpp"
#include "MainData.hpp"



UI::Control::Main::Layout::Layout()
	: ::Attribute::Layout(0, sizeof(Main::Data))
	, Pos(*this)
{ }
