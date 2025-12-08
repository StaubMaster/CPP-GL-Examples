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
	unsigned int indexPallet
) :
	Pos(divisor, stride, indexPos),
	Pallet(divisor, stride, indexPallet)
{ }
void UI::Text::Inst_Attribute::Bind(const unsigned char * & offset) const
{
	Pos.Bind(offset);
	Pallet.Bind(offset);
}



UI::Text::BufferArray::BufferArray() :
	Main(1, (Attribute::Base * []) { new Main_Attribute(0, sizeof(UI::Text::Main_Data), 0) }),
	Inst(1, (Attribute::Base * []) { new Inst_Attribute(1, sizeof(UI::Text::Inst_Data), 1, 2) })
{ }
void UI::Text::BufferArray::Draw()
{
	glDrawArraysInstanced(GL_TRIANGLES, 0, Main.Count, Inst.Count);
}
