#include "BufferLayout.hpp"
#include "BufferData.hpp"

#include "OpenGL.hpp"



UI::Control::Main::BufferLayout::~BufferLayout() { }
UI::Control::Main::BufferLayout::BufferLayout()
	: ::Attribute::Layout(0, sizeof(Main::BufferData))
	, Pos(*this)
{ }



UI::Control::Inst::BufferLayout::~BufferLayout() { }
UI::Control::Inst::BufferLayout::BufferLayout()
	: ::Attribute::Layout(1, sizeof(Inst::BufferData))
	, Box(*this)
	, Layer(*this)
	, Col(*this)
{ }
