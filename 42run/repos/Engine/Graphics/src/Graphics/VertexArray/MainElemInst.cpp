#include "Graphics/VertexArray/MainElemInst.hpp"
#include "OpenGL.hpp"



VertexArray::MainElemInst::~MainElemInst()
{ }
VertexArray::MainElemInst::MainElemInst()
	: Base()
	, Mode(GL::DrawMode::Lines)
	, MainBuffer(GL::BufferDataUsage::StaticDraw)
	, ElemBuffer(GL::BufferDataUsage::StaticDraw, GL::DrawIndexType::UnsignedInt)
	, InstBuffer(GL::BufferDataUsage::DynamicDraw)
{ }



void VertexArray::MainElemInst::Create()
{
	Base::Create();
	MainBuffer.Create();
	ElemBuffer.Create();
	InstBuffer.Create();
}
void VertexArray::MainElemInst::Delete()
{
	Base::Delete();
	MainBuffer.Delete();
	ElemBuffer.Delete();
	InstBuffer.Delete();
}

void VertexArray::MainElemInst::Init()
{
	Bind();

	MainBuffer.Init();

	ElemBuffer.Bind();

	InstBuffer.Init();
}

void VertexArray::MainElemInst::Draw()
{
	GL::DrawElementsInstanced(Mode, ElemBuffer.Count, ElemBuffer.IndexType, InstBuffer.Count);
}
