#include "Buffer.hpp"
#include "Data.hpp"

#include "OpenGL/openGL.h"



UI::Control::Main_Attribute::Main_Attribute(
	unsigned int divisor,
	unsigned int stride,
	unsigned int indexPos
) :
	Pos(divisor, stride, indexPos)
{ }
void UI::Control::Main_Attribute::Bind(const unsigned char * & offset) const
{
	Pos.Bind(offset);
}



UI::Control::Inst_Attribute::Inst_Attribute(
	unsigned int divisor,
	unsigned int stride,
	unsigned int indexMin,
	unsigned int indexMax,
	unsigned int indexLayer,
	unsigned int indexCol
) :
	Min(divisor, stride, indexMin),
	Max(divisor, stride, indexMax),
	Layer(divisor, stride, indexLayer),
	Col(divisor, stride, indexCol)
{ }
void UI::Control::Inst_Attribute::Bind(const unsigned char * & offset) const
{
	Min.Bind(offset);
	Max.Bind(offset);
	Layer.Bind(offset);
	Col.Bind(offset);
}




UI::Control::BufferArray::BufferArray() :
	Main(1, (Attribute::Base * []) { new Main_Attribute(0, sizeof(UI::Control::Main_Data), 0) }),
	Inst(1, (Attribute::Base * []) { new Inst_Attribute(1, sizeof(UI::Control::Inst_Data), 1, 2, 3, 4) })
{ }
void UI::Control::BufferArray::Draw()
{
	glDrawArraysInstanced(GL_TRIANGLES, 0, Main.Count, Inst.Count);
}
