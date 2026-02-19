#include "PolyGon/Physics2D/BufferArray.hpp"

#include "OpenGL.hpp"



Physics2D::BufferArray::BufferArray() :
	Main(*this, 0, 1),
	Inst(*this, 2, 3, 5, 6),
	DrawMode(GL::DrawMode::Triangles)
{
	Buffers.Allocate(2),
	Buffers.Insert(&Main);
	Buffers.Insert(&Inst);
}



void Physics2D::BufferArray::Draw()
{
	Bind();
	GL::DrawArraysInstanced(DrawMode, 0, Main.DrawCount, Inst.DrawCount);
}
