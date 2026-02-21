#include "PolyGon/Physics2D/BufferArray.hpp"

#include "OpenGL.hpp"



Physics2D::BufferArray::BufferArray()
	: ::BufferArray::Base()
	, Main(*this)
	, Inst(*this)
	, DrawMode(GL::DrawMode::Triangles)
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
