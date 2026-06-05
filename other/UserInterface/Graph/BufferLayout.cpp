#include "BufferLayout.hpp"
#include "BufferData.hpp"

#include "OpenGL.hpp"



UI::Graph::BufferLayout::~BufferLayout() { }
UI::Graph::BufferLayout::BufferLayout()
	: ::Attribute::Layout(0, sizeof(BufferData))
	, Box(*this)
	, Pos(*this)
	, Col(*this)
{ }
