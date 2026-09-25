#include "Graphics/VertexArray/MainInst.hpp"
#include "OpenGL.hpp"



VertexArray::MainInst::~MainInst()
{ }
VertexArray::MainInst::MainInst()
	: Base()
	, Mode(GL::DrawMode::Triangles)
	, MainBuffer(GL::BufferDataUsage::StaticDraw)
	, InstBuffer(GL::BufferDataUsage::DynamicDraw)
{ }



void VertexArray::MainInst::Create()
{
	Base::Create();
	MainBuffer.Create();
	InstBuffer.Create();
}
void VertexArray::MainInst::Delete()
{
	Base::Delete();
	MainBuffer.Delete();
	InstBuffer.Delete();
}

void VertexArray::MainInst::Init()
{
	Bind();

	MainBuffer.Init();

	InstBuffer.Init();
}

void VertexArray::MainInst::Draw()
{
	GL::DrawArraysInstanced(Mode, 0, MainBuffer.Count, InstBuffer.Count);
}
