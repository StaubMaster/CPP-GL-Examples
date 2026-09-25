#include "Graphics/VertexArray/Main.hpp"
#include "OpenGL.hpp"



VertexArray::Main::~Main()
{ }
VertexArray::Main::Main()
	: Base()
	, Mode(GL::DrawMode::Triangles)
	, MainBuffer(GL::BufferDataUsage::StaticDraw)
{ }



void VertexArray::Main::Create()
{
	Base::Create();
	MainBuffer.Create();
}
void VertexArray::Main::Delete()
{
	Base::Delete();
	MainBuffer.Delete();
}

void VertexArray::Main::Init()
{
	Bind();

	MainBuffer.Init();
}

void VertexArray::Main::Draw()
{
	GL::DrawArrays(Mode, 0, MainBuffer.Count);
}
