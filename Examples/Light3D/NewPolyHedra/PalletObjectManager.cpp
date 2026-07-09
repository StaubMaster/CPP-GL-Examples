#include "PalletObjectManager.hpp"
#include "Pallet.hpp"

#include "Graphics/Attribute/General/Layout.hpp"
#include "OpenGL.hpp"



NewPolyHedra::PalletObjectManager::~PalletObjectManager()
{ }
NewPolyHedra::PalletObjectManager::PalletObjectManager()
	: Pallet(nullptr)
	, BufferFullVertexArray()
	, BufferWireVertexArray()
	, BufferFull(GL::BufferDataUsage::StreamDraw)
	, BufferWire(GL::BufferDataUsage::StreamDraw)
{ }

NewPolyHedra::PalletObjectManager::PalletObjectManager(NewPolyHedra::Pallet * pallet)
	: Pallet(pallet)
	, BufferFullVertexArray()
	, BufferWireVertexArray()
	, BufferFull(GL::BufferDataUsage::StreamDraw)
	, BufferWire(GL::BufferDataUsage::StreamDraw)
{ }



void NewPolyHedra::PalletObjectManager::VertexBufferInit()
{
	BufferFullVertexArray.Bind();
	{
		BufferFull.Bind();
		BufferFull.Update();
		if (Pallet != nullptr)
		{
			Pallet -> BufferFull.Bind();
			if (Pallet -> BufferFullLayout != nullptr)
			{
				Pallet -> BufferFullLayout -> Bind();
			}
		}
		if (BufferUniform != nullptr)
		{
			BufferUniform -> Bind();
		}
	}
	BufferWireVertexArray.Bind();
	{
		BufferWire.Bind();
		BufferWire.Update();
		if (Pallet != nullptr)
		{
			Pallet -> BufferWire.Bind();
			if (Pallet -> BufferWireLayout != nullptr)
			{
				Pallet -> BufferWireLayout -> Bind();
			}
			Pallet -> BufferWireElem.Bind();
		}
	}
	VertexArray::BindNone();
}

void NewPolyHedra::PalletObjectManager::GraphicsCreate()
{
	BufferFullVertexArray.Create();
	BufferWireVertexArray.Create();
	BufferFull.Create();
	BufferWire.Create();
}
void NewPolyHedra::PalletObjectManager::GraphicsDelete()
{
	BufferFullVertexArray.Delete();
	BufferWireVertexArray.Delete();
	BufferFull.Delete();
	BufferWire.Delete();
}
void NewPolyHedra::PalletObjectManager::GraphicsDrawFull()
{
	InstancesToBufferFull();
	if (Pallet != nullptr)
	{
		BufferFullVertexArray.Bind();
		Pallet -> Texture.Bind();
		GL::DrawArraysInstanced(GL::DrawMode::Triangles, 0
			, Pallet -> BufferFull.Count
			, BufferFull.Count
		);
	}
}
void NewPolyHedra::PalletObjectManager::GraphicsDrawWire()
{
	InstancesToBufferWire();
	if (Pallet != nullptr)
	{
		BufferWireVertexArray.Bind();
		GL::DrawElementsInstanced(GL::DrawMode::Lines
			, Pallet -> BufferWireElem.Count
			, Pallet -> BufferWireElem.IndexType
			, BufferWire.Count
		);
	}
}
