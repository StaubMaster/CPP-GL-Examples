#include "PalletObjectManager.hpp"
#include "Pallet.hpp"

#include "Graphics/Attribute/General/Layout.hpp"
#include "OpenGL.hpp"



NewPolyHedra::PalletObjectManager::~PalletObjectManager()
{ }
NewPolyHedra::PalletObjectManager::PalletObjectManager()
	: Pallet(nullptr)
	, BufferFull()
	, BufferWire()
	, BufferFullInstance(GL::BufferDataUsage::StreamDraw)
	, BufferWireInstance(GL::BufferDataUsage::StreamDraw)
{ }

NewPolyHedra::PalletObjectManager::PalletObjectManager(NewPolyHedra::Pallet * pallet)
	: Pallet(pallet)
	, BufferFull()
	, BufferWire()
	, BufferFullInstance(GL::BufferDataUsage::StreamDraw)
	, BufferWireInstance(GL::BufferDataUsage::StreamDraw)
{ }



void NewPolyHedra::PalletObjectManager::GraphicsCreate()
{
	BufferFull.Create();
	BufferWire.Create();
	BufferFullInstance.Create();
	BufferWireInstance.Create();
}
void NewPolyHedra::PalletObjectManager::GraphicsDelete()
{
	BufferFull.Delete();
	BufferWire.Delete();
	BufferFullInstance.Delete();
	BufferWireInstance.Delete();
}

void NewPolyHedra::PalletObjectManager::GraphicsDrawFull()
{
	InstancesToBufferFull();
	if (Pallet != nullptr)
	{
		BufferFull.Bind();
		Pallet -> Texture.Bind();
		GL::DrawArraysInstanced(GL::DrawMode::Triangles, 0, Pallet -> CountFull, CountFull);
	}
}
void NewPolyHedra::PalletObjectManager::GraphicsDrawWire()
{
	InstancesToBufferWire();
	if (Pallet != nullptr)
	{
		BufferWire.Bind();
		GL::DrawElementsInstanced(GL::DrawMode::Lines
			, Pallet -> CountWire
			, Pallet -> BufferWireElem.IndexType
			, CountWire
		);
	}
}
