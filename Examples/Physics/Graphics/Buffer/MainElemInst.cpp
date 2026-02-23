#include "Graphics/Buffer/MainElemInst.hpp"
#include "Graphics/Texture/Base.hpp"
#include "OpenGL.hpp"



BufferArray::MainElemInst::~MainElemInst() { }
BufferArray::MainElemInst::MainElemInst(GL::DrawMode mode)
	: BufferArray::Base()
	, Mode(mode)
	, MainPtr(nullptr)
	, ElemPtr(nullptr)
	, InstPtr(nullptr)
	, Textures()
{ }

void BufferArray::MainElemInst::Draw()
{
	if (MainPtr == nullptr || ElemPtr == nullptr || InstPtr == nullptr) { return; }
	for (unsigned int i = 0; i < Textures.Count(); i++)
	{
		Textures[i] -> Bind();
	}
	Bind();
	GL::DrawElementsInstanced(Mode, ElemPtr -> DrawCount, ElemPtr -> IndexType, InstPtr -> DrawCount);
}
