#include "NewPolyHedra/Base/Display/Object.hpp"

#include "NewPolyHedra/Pallet/.hpp"

#include "Graphics/Attribute/General/Layout.hpp"
#include "OpenGL.hpp"



bool NewPolyHedra::BaseDisplayObject::Equals(const NewPolyHedra::Pallet * pallet) const { return (&PalletObject == pallet); }
bool NewPolyHedra::BaseDisplayObject::Equals(const NewPolyHedra::Pallet & pallet) const { return (&PalletObject == &pallet); }



NewPolyHedra::BaseDisplayObject::BaseDisplayObject(Pallet & pallet)
	: PalletObject(pallet)
	, BufferFull()
	, BufferWire()
	, BufferFullInstance(GL::BufferDataUsage::StreamDraw)
	, BufferWireInstance(GL::BufferDataUsage::StreamDraw)
{ }



void NewPolyHedra::BaseDisplayObject::GraphicsCreate()
{
	BufferFull.Create();
	BufferWire.Create();
	BufferFullInstance.Create();
	BufferWireInstance.Create();
}
void NewPolyHedra::BaseDisplayObject::GraphicsDelete()
{
	BufferFull.Delete();
	BufferWire.Delete();
	BufferFullInstance.Delete();
	BufferWireInstance.Delete();
}

void NewPolyHedra::BaseDisplayObject::GraphicsInitFull(::Attribute::Layout & layout_main, ::Attribute::Layout * layout_inst)
{
	BufferFull.Bind();

	PalletObject.GraphicsInitFull();
	layout_main.Bind();

	BufferFullInstance.Bind();
	if (layout_inst != nullptr)
	{
		layout_inst -> Bind();
	}
}
void NewPolyHedra::BaseDisplayObject::GraphicsInitWire(::Attribute::Layout & layout_main, ::Attribute::Layout * layout_inst)
{
	BufferWire.Bind();

	PalletObject.GraphicsInitWire();
	layout_main.Bind();

	BufferWireInstance.Bind();
	if (layout_inst != nullptr)
	{
		layout_inst -> Bind();
	}
}

void NewPolyHedra::BaseDisplayObject::GraphicsDrawFull()
{
	InstancesFullToBuffer();
	BufferFull.Bind();
	PalletObject.Texture.Bind();
	GL::DrawArraysInstanced(GL::DrawMode::Triangles, 0, PalletObject.BufferFull.Count, CountFull);
}
void NewPolyHedra::BaseDisplayObject::GraphicsDrawWire()
{
	InstancesWireToBuffer();
	BufferWire.Bind();
	GL::DrawElementsInstanced(GL::DrawMode::Lines
		, PalletObject.BufferWireElem.Count
		, PalletObject.BufferWireElem.IndexType
		, CountWire
	);
}
