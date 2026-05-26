#include "Buffer.hpp"
#include "Data.hpp"

#include "OpenGL.hpp"



UI::Control::Main_Layout::~Main_Layout() { }
UI::Control::Main_Layout::Main_Layout()
	: ::Attribute::Layout(0, sizeof(Main_Data))
	, Pos(*this)
{ }



UI::Control::Inst_Layout::~Inst_Layout() { }
UI::Control::Inst_Layout::Inst_Layout()
	: ::Attribute::Layout(1, sizeof(Inst_Data))
	, Min(*this)
	, Max(*this)
	, Layer(*this)
	, Col(*this)
{ }
