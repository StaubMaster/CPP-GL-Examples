#include "Buffer.hpp"
#include "Data.hpp"

#include "OpenGL/openGL.h"



UI::Text::Main_Attribute::Main_Attribute(
	unsigned int divisor,
	unsigned int stride,
	unsigned int indexPos
) :
	Pos(divisor, stride, indexPos)
{ }
void UI::Text::Main_Attribute::Bind(const unsigned char * & offset) const
{
	Pos.Bind(offset);
}



UI::Text::Inst_Attribute::Inst_Attribute(
	unsigned int divisor,
	unsigned int stride,
	unsigned int indexPos,
	unsigned int indexPalletMin,
	unsigned int indexPalletMax,
	unsigned int indexBoundMin,
	unsigned int indexBoundMax
) :
	Pos(divisor, stride, indexPos),
	PalletMin(divisor, stride, indexPalletMin),
	PalletMax(divisor, stride, indexPalletMax),
	BoundMin(divisor, stride, indexBoundMin),
	BoundMax(divisor, stride, indexBoundMax)
{ }
void UI::Text::Inst_Attribute::Bind(const unsigned char * & offset) const
{
	Pos.Bind(offset);
	PalletMin.Bind(offset);
	PalletMax.Bind(offset);
	BoundMin.Bind(offset);
	BoundMax.Bind(offset);
}



UI::Text::BufferArray::BufferArray() :
	Main(1, (Attribute::Base * []) { new Main_Attribute(0, sizeof(UI::Text::Main_Data), 0) }),
	Inst(1, (Attribute::Base * []) { new Inst_Attribute(1, sizeof(UI::Text::Inst_Data), 1, 2, 3, 4, 5) })
{ }
void UI::Text::BufferArray::Draw()
{
	glDrawArraysInstanced(GL_TRIANGLES, 0, Main.Count, Inst.Count);
}
