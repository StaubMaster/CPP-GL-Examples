#include "Buffer.hpp"
#include "Data.hpp"

#include "OpenGL.hpp"



UI::Text::Main_Buffer::Main_Buffer(
	unsigned int indexPos
) :
	::Buffer::Attribute(GL::BufferTarget::ArrayBuffer, GL::BufferDataUsage::StaticDraw, sizeof(Main_Data)),
	Pos(0, sizeof(Main_Data), indexPos)
{
	Attributes.Allocate(1);
	Attributes.Insert(&Pos);
}



UI::Text::Inst_Buffer::Inst_Buffer(
	unsigned int indexPos,
	unsigned int indexPalletMin,
	unsigned int indexPalletMax,
	unsigned int indexBoundMin,
	unsigned int indexBoundMax
) :
	::Buffer::Attribute(GL::BufferTarget::ArrayBuffer, GL::BufferDataUsage::StreamDraw, sizeof(Inst_Data)),
	Pos(1, sizeof(Inst_Data), indexPos),
	PalletMin(1, sizeof(Inst_Data), indexPalletMin),
	PalletMax(1, sizeof(Inst_Data), indexPalletMax),
	BoundMin(1, sizeof(Inst_Data), indexBoundMin),
	BoundMax(1, sizeof(Inst_Data), indexBoundMax)
{
	Attributes.Allocate(5);
	Attributes.Insert(&Pos);
	Attributes.Insert(&PalletMin);
	Attributes.Insert(&PalletMax);
	Attributes.Insert(&BoundMin);
	Attributes.Insert(&BoundMax);
}



UI::Text::BufferArray::BufferArray() :
	Main(0),
	Inst(1, 2, 3, 4, 5),
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
