#include "Buffer.hpp"
#include "Data.hpp"

#include "OpenGL/openGL.h"



UI::Text::Main_Buffer::Main_Buffer(
	unsigned int indexPos
) :
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
	DrawMode(GL_TRIANGLES)
{ }
void UI::Text::BufferArray::Draw()
{
	glDrawArraysInstanced(DrawMode, 0, Main.DrawCount, Inst.DrawCount);
}
