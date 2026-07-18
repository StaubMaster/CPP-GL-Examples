#include "Pallet.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Data.hpp"
#include "PolyHedra/Skin/Skin.hpp"

#include "PolyHedra/Graphics/Full/Main/Data.hpp"
#include "PolyHedra/Graphics/Wire/Main/Data.hpp"

#include "Graphics/VertexArray/Base.hpp"
#include "Graphics/Attribute/General/Layout.hpp"



NewPolyHedra::Pallet::~Pallet()
{
	delete Object;
}
NewPolyHedra::Pallet::Pallet()
	: Object(nullptr)
	, Name()
	, BufferFull(GL::BufferDataUsage::StaticDraw)
	, BufferWire(GL::BufferDataUsage::StaticDraw)
	, BufferWireElem(GL::BufferDataUsage::StaticDraw, GL::DrawIndexType::UnsignedInt)
	, Texture()
{ }
NewPolyHedra::Pallet::Pallet(PolyHedra * object)
	: Object(object)
	, Name()
	, BufferFull(GL::BufferDataUsage::StaticDraw)
	, BufferWire(GL::BufferDataUsage::StaticDraw)
	, BufferWireElem(GL::BufferDataUsage::StaticDraw, GL::DrawIndexType::UnsignedInt)
	, Texture()
{ }
NewPolyHedra::Pallet::Pallet(PolyHedra * object, std::string name)
	: Object(object)
	, Name(name)
	, BufferFull(GL::BufferDataUsage::StaticDraw)
	, BufferWire(GL::BufferDataUsage::StaticDraw)
	, BufferWireElem(GL::BufferDataUsage::StaticDraw, GL::DrawIndexType::UnsignedInt)
	, Texture()
{ }



void NewPolyHedra::Pallet::GraphicsPut()
{
	VertexArray::Base::BindNone();
	if (Object != nullptr)
	{
		Object -> CalcNormals();
		{
			Container::Array<PolyHedraFull::Main::Data> data = Object -> ToMainData();
			BufferFull.DataFull(data.ToVoid());
			BufferFull.Count = data.Length();
		}
		{
			Container::Array<PolyHedraWire::Main::Data> data(Object -> Corners.Count());
			for (unsigned int i = 0; i < Object -> Corners.Count(); i++)
			{
				data[i] = PolyHedraWire::Main::Data(Object -> Corners[i].Position, ColorF4(1, 1, 1));
			}
			BufferWire.DataFull(data.ToVoid());
			BufferWire.Count = data.Length();
		}
		{
			Container::Array<PolyHedra::Edge> data = Object -> Edges.ToArray();
			BufferWireElem.DataFull(data.ToVoid());
			BufferWireElem.Count = data.Length();
		}
		Texture = Object -> Skins[0] -> ToTexture();
	}
}
void NewPolyHedra::Pallet::GraphicsInitFull()
{
	BufferFull.Init();
}
void NewPolyHedra::Pallet::GraphicsInitWire()
{
	BufferWire.Init();
	BufferWireElem.Bind();
}

void NewPolyHedra::Pallet::GraphicsCreate()
{
	BufferFull.Create();
	BufferWire.Create();
	BufferWireElem.Create();
}
void NewPolyHedra::Pallet::GraphicsDelete()
{
	BufferFull.Delete();
	BufferWire.Delete();
	BufferWireElem.Delete();
}
