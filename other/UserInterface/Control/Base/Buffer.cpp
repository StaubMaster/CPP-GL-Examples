#include "Buffer.hpp"
#include "Data.hpp"

#include "OpenGL.hpp"



UI::Control::Main_Buffer::~Main_Buffer() { }
UI::Control::Main_Buffer::Main_Buffer(::VertexArray & vertex_array)
	: ::Buffer::Array(vertex_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(Main_Data))
	, Pos()
{
	Attributes.Allocate(1);
	Attributes.Insert(&Pos);
}



UI::Control::Inst_Buffer::~Inst_Buffer() { }
UI::Control::Inst_Buffer::Inst_Buffer(::VertexArray & vertex_array)
	: ::Buffer::Array(vertex_array, GL::BufferDataUsage::StreamDraw, 1, sizeof(Inst_Data))
	, Min()
	, Max()
	, Layer()
	, Col()
{
	Attributes.Allocate(4);
	Attributes.Insert(&Min);
	Attributes.Insert(&Max);
	Attributes.Insert(&Layer);
	Attributes.Insert(&Col);
}



UI::Control::Buffer::~Buffer() { }
UI::Control::Buffer::Buffer()
	: ::VertexArray()
	, Main(*this)
	, Inst(*this)
	, DrawMode(GL::DrawMode::Triangles)
{
	Buffers.Allocate(2);
	Buffers.Insert(&Main);
	Buffers.Insert(&Inst);
}
void UI::Control::Buffer::Draw()
{
	Bind();
	GL::DrawArraysInstanced(DrawMode, 0, Main.Count, Inst.Count);
}
