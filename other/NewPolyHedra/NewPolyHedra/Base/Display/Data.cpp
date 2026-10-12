#include "NewPolyHedra/Base/Display/Data.hpp"

#include "NewPolyHedra/Pallet/.hpp"

#include "Graphics/Attribute/General/Layout.hpp"
#include "OpenGL.hpp"



bool NewPolyHedra::BaseDisplayData::Equals(const NewPolyHedra::Pallet * pallet) const { return (&PalletObject == pallet); }
bool NewPolyHedra::BaseDisplayData::Equals(const NewPolyHedra::Pallet & pallet) const { return (&PalletObject == &pallet); }



NewPolyHedra::BaseDisplayData::BaseDisplayData(Pallet & pallet)
	: PalletObject(pallet)
	, BufferFull()
	, BufferWire()
	, BufferFullInstance(GL::BufferDataUsage::StreamDraw)
	, BufferWireInstance(GL::BufferDataUsage::StreamDraw)
{ }



void NewPolyHedra::BaseDisplayData::GraphicsCreate()
{
	BufferFull.Create();
	BufferWire.Create();
	BufferFullInstance.Create();
	BufferWireInstance.Create();
}
void NewPolyHedra::BaseDisplayData::GraphicsDelete()
{
	BufferFull.Delete();
	BufferWire.Delete();
	BufferFullInstance.Delete();
	BufferWireInstance.Delete();
}

void NewPolyHedra::BaseDisplayData::GraphicsInitFull(::Attribute::Layout * layout)
{
	BufferFull.Bind();
	BufferFullInstance.Bind();
	if (layout != nullptr)
	{
		layout -> Bind();
	}
	PalletObject.GraphicsInitFull();
}
void NewPolyHedra::BaseDisplayData::GraphicsInitWire(::Attribute::Layout * layout)
{
	BufferWire.Bind();
	BufferWireInstance.Bind();
	if (layout != nullptr)
	{
		layout -> Bind();
	}
	PalletObject.GraphicsInitWire();
}

void NewPolyHedra::BaseDisplayData::GraphicsDrawFull()
{
	InstancesFullToBuffer();
	BufferFull.Bind();
	PalletObject.Texture.Bind();
	GL::DrawArraysInstanced(GL::DrawMode::Triangles, 0, PalletObject.BufferFull.Count, CountFull);
}
void NewPolyHedra::BaseDisplayData::GraphicsDrawWire()
{
	InstancesWireToBuffer();
	BufferWire.Bind();
	GL::DrawElementsInstanced(GL::DrawMode::Lines
		, PalletObject.BufferWireElem.Count
		, PalletObject.BufferWireElem.IndexType
		, CountWire
	);
}
