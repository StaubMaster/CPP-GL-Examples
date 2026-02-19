#include "Arrow2D/Buffer.hpp"

#include "OpenGL.hpp"



Arrow2D::Buffer::~Buffer() { }
Arrow2D::Buffer::Buffer()
	: ::BufferArray::MainInst(GL::DrawMode::Triangles)
	, Main(*this, 0, 1)
	, Inst(*this, 2, 3, 4, 5)
{
	MainPtr = &Main;
	InstPtr = &Inst;

	Buffers.Allocate(2),
	Buffers.Insert(&Main);
	Buffers.Insert(&Inst);
}
