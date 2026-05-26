#include "Buffer.hpp"
#include "Data.hpp"

#include "OpenGL.hpp"



UI::Text::Main_Layout::Main_Layout()
	: ::Attribute::Layout(0, sizeof(Main_Data))
	, Pos(*this)
{ }



UI::Text::Inst_Layout::Inst_Layout()
	: ::Attribute::Layout(1, sizeof(Inst_Data))
	, Pos(*this)
	, PalletIdx(*this)
	, TextIdx(*this)
{ }
