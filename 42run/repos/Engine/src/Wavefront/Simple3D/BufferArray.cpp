#include "Wavefront/Simple3D/BufferArray.hpp"
#include "OpenGL.hpp"



Wavefront::Simple3D::BufferArray::~BufferArray() { }

Wavefront::Simple3D::BufferArray::BufferArray()
	: ::VertexArray()
	, Main(*this)
	, Inst(*this)
	, DrawMode(GL::DrawMode::Triangles)
{
	Buffers.Allocate(2);
	Buffers.Insert(&Main);
	Buffers.Insert(&Inst);
}



void Wavefront::Simple3D::BufferArray::Draw()
{
	Bind();
	GL::DrawArraysInstanced(DrawMode, 0, Main.DrawCount, Inst.DrawCount);
}
