#include "Buffer.hpp"
#include "Data.hpp"

#include "OpenGL.hpp"



UI::Text::Main_Buffer::Main_Buffer(::BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(Main_Data))
	, Pos()
{
	Attributes.Allocate(1);
	Attributes.Insert(&Pos);
}



UI::Text::Inst_Buffer::Inst_Buffer(::BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StreamDraw, 1, sizeof(Inst_Data))
	, Pos()
	, PalletMin()
	, PalletMax()
	, BoundMin()
	, BoundMax()
{
	Attributes.Allocate(5);
	Attributes.Insert(&Pos);
	Attributes.Insert(&PalletMin);
	Attributes.Insert(&PalletMax);
	Attributes.Insert(&BoundMin);
	Attributes.Insert(&BoundMax);
}



UI::Text::Buffer::~Buffer() { }

UI::Text::Buffer::Buffer()
	: ::BufferArray::Base()
	, Main(*this)
	, Inst(*this)
	, DrawMode(GL::DrawMode::Triangles)
{
	Buffers.Allocate(2);
	Buffers.Insert(&Main);
	Buffers.Insert(&Inst);

	Main.Pos.Change(0);
	Inst.Pos.Change(1);
	Inst.PalletMin.Change(2);
	Inst.PalletMax.Change(3);
	Inst.BoundMin.Change(4);
	Inst.BoundMax.Change(5);
}
void UI::Text::Buffer::Draw()
{
	GL::DrawArraysInstanced(DrawMode, 0, Main.DrawCount, Inst.DrawCount);
}
