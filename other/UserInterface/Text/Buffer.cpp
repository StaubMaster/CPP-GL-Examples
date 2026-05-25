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



UI::Text::Buffer::~Buffer() { }

UI::Text::Buffer::Buffer()
	: ::VertexArray()
	, Main(*this, GL::BufferDataUsage::StaticDraw)
	, Inst(*this, GL::BufferDataUsage::StreamDraw)
	, DrawMode(GL::DrawMode::Triangles)
{
	Buffers.Insert(&Main);
	Buffers.Insert(&Inst);
	Buffers.Trim();
}
void UI::Text::Buffer::Draw()
{
	GL::DrawArraysInstanced(DrawMode, 0, Main.Count, Inst.Count);
}
