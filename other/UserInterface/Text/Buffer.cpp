#include "Buffer.hpp"
#include "Data.hpp"

#include "OpenGL.hpp"



UI::Text::Main_Buffer::Main_Buffer(
	::BufferArray::Base & buffer_array,
	unsigned int indexPos
)	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(Main_Data))
	, Pos()
{
	Attributes.Allocate(1);
	Attributes.Insert(&Pos);

	Pos.Change(indexPos);
}



UI::Text::Inst_Buffer::Inst_Buffer(
	::BufferArray::Base & buffer_array,
	unsigned int indexPos,
	unsigned int indexPalletMin,
	unsigned int indexPalletMax,
	unsigned int indexBoundMin,
	unsigned int indexBoundMax
)	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StreamDraw, 1, sizeof(Inst_Data))
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

	Pos.Change(indexPos);
	PalletMin.Change(indexPalletMin);
	PalletMax.Change(indexPalletMax);
	BoundMin.Change(indexBoundMin);
	BoundMax.Change(indexBoundMax);
}



UI::Text::BufferArray::BufferArray() :
	Main(*this, 0),
	Inst(*this, 1, 2, 3, 4, 5),
	DrawMode(GL::DrawMode::Triangles)
{
	Buffers.Allocate(2);
	Buffers.Insert(&Main);
	Buffers.Insert(&Inst);
}
void UI::Text::BufferArray::Draw()
{
	GL::DrawArraysInstanced(DrawMode, 0, Main.DrawCount, Inst.DrawCount);
}
