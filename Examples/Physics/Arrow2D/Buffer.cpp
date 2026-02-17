#include "Arrow2D/Buffer.hpp"

#include "OpenGL.hpp"



Arrow2D::Buffer::Buffer() :
	Main(0, 1),
	Inst(2, 3, 4),
	DrawMode(GL::DrawMode::Triangles)
{
	Buffers.Allocate(2),
	Buffers.Insert(&Main);
	Buffers.Insert(&Inst);
}



void Arrow2D::Buffer::Draw()
{
	Bind();
	GL::DrawArraysInstanced(DrawMode, 0, Main.DrawCount, Inst.DrawCount);
}
