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



UI::Control::Buffer::~Buffer() { }
UI::Control::Buffer::Buffer()
	: ::VertexArray()
	, Main(*this, GL::BufferDataUsage::StaticDraw)
	, Inst(*this, GL::BufferDataUsage::StreamDraw)
	, DrawMode(GL::DrawMode::Triangles)
{
	Buffers.Insert(&Main);
	Buffers.Insert(&Inst);
	Buffers.Trim();
}
void UI::Control::Buffer::Draw()
{
	Bind();
	GL::DrawArraysInstanced(DrawMode, 0, Main.Count, Inst.Count);
}
