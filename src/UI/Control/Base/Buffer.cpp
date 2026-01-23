#include "Buffer.hpp"
#include "Data.hpp"

#include "OpenGL/openGL.h"



UI::Control::Main_Buffer::Main_Buffer(
	unsigned int indexPos
) :
	Pos(0, sizeof(Main_Data), indexPos)
{
	Attributes.Allocate(1);
	Attributes.Insert(&Pos);
}



UI::Control::Inst_Buffer::Inst_Buffer(
	unsigned int indexMin,
	unsigned int indexMax,
	unsigned int indexLayer,
	unsigned int indexCol
) :
	Min(1, sizeof(Inst_Data), indexMin),
	Max(1, sizeof(Inst_Data), indexMax),
	Layer(1, sizeof(Inst_Data), indexLayer),
	Col(1, sizeof(Inst_Data), indexCol)
{
	Attributes.Allocate(4);
	Attributes.Insert(&Min);
	Attributes.Insert(&Max);
	Attributes.Insert(&Layer);
	Attributes.Insert(&Col);
}



//#include "Debug.hpp"
//#include <sstream>

UI::Control::BufferArray::BufferArray() :
	Main(0),
	Inst(1, 2, 3, 4),
	DrawMode(GL_TRIANGLES)
{
	Buffers.Allocate(2);
	Buffers.Insert(&Main);
	Buffers.Insert(&Inst);
}
void UI::Control::BufferArray::Draw()
{
	//Debug::Log << "Draw: " << Main.DrawCount << " " << Inst.DrawCount << Debug::Done;
	Bind();
	glDrawArraysInstanced(DrawMode, 0, Main.DrawCount, Inst.DrawCount);
}
