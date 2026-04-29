#include "Buffer.hpp"
#include "Data.hpp"

#include "OpenGL.hpp"



UI::Text::Main_Buffer::Main_Buffer(::VertexArray & vertex_array)
	: ::Buffer::Array(vertex_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(Main_Data))
	, Pos(*this)
{ }



UI::Text::Inst_Buffer::Inst_Buffer(::VertexArray & vertex_array)
	: ::Buffer::Array(vertex_array, GL::BufferDataUsage::StreamDraw, 1, sizeof(Inst_Data))
	, Pos(*this)
	, Pallet(*this)
	, Bound(*this)
	, Color(*this)
{ }



UI::Text::Buffer::~Buffer() { }

UI::Text::Buffer::Buffer()
	: ::VertexArray()
	, Main(*this)
	, Inst(*this)
	, DrawMode(GL::DrawMode::Triangles)
{
	Buffers.Allocate(2);
	Buffers.Insert(&Main);
	Buffers.Insert(&Inst);
}
void UI::Text::Buffer::Draw()
{
	GL::DrawArraysInstanced(DrawMode, 0, Main.Count, Inst.Count);
}
