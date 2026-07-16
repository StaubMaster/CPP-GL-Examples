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
	, BufferFullLayout(nullptr)
	, BufferWireLayout(nullptr)
	, Texture()
{
	BufferFull.SizeOf = sizeof(PolyHedraFull::Main::Data);
	BufferWire.SizeOf = sizeof(PolyHedraWire::Main::Data);
}
NewPolyHedra::Pallet::Pallet(PolyHedra * object)
	: Object(object)
	, Name()
	, BufferFull(GL::BufferDataUsage::StaticDraw)
	, BufferWire(GL::BufferDataUsage::StaticDraw)
	, BufferWireElem(GL::BufferDataUsage::StaticDraw, GL::DrawIndexType::UnsignedInt)
	, BufferFullLayout(nullptr)
	, BufferWireLayout(nullptr)
	, Texture()
{
	BufferFull.SizeOf = sizeof(PolyHedraFull::Main::Data);
	BufferWire.SizeOf = sizeof(PolyHedraWire::Main::Data);
}
NewPolyHedra::Pallet::Pallet(PolyHedra * object, std::string name)
	: Object(object)
	, Name(name)
	, BufferFull(GL::BufferDataUsage::StaticDraw)
	, BufferWire(GL::BufferDataUsage::StaticDraw)
	, BufferWireElem(GL::BufferDataUsage::StaticDraw, GL::DrawIndexType::UnsignedInt)
	, BufferFullLayout(nullptr)
	, BufferWireLayout(nullptr)
	, Texture()
{
	BufferFull.SizeOf = sizeof(PolyHedraFull::Main::Data);
	BufferWire.SizeOf = sizeof(PolyHedraWire::Main::Data);
}



void NewPolyHedra::Pallet::GraphicsPut()
{
	VertexArray::Base::BindNone();
	if (Object != nullptr)
	{
		Object -> CalcNormals();
		{
			Container::Array<PolyHedraFull::Main::Data> data = Object -> ToMainData();
			BufferFull.DataFull(data.ToVoid());
		}
		{
			Container::Array<PolyHedraWire::Main::Data> data(Object -> Corners.Count());
			for (unsigned int i = 0; i < Object -> Corners.Count(); i++)
			{
				data[i] = PolyHedraWire::Main::Data(Object -> Corners[i].Position, ColorF4(1, 1, 1));
			}
			BufferWire.DataFull(data.ToVoid());
		}
		{
			BufferWireElem.DataFull(Object -> Edges.ToVoid());
		}
		Texture = Object -> Skins[0] -> ToTexture();
	}
}
void NewPolyHedra::Pallet::GraphicsInitFull()
{
	BufferFull.Bind();
	if (BufferFullLayout != nullptr)
	{
		BufferFullLayout -> Bind();
	}
}
void NewPolyHedra::Pallet::GraphicsInitWire()
{
	BufferWire.Bind();
	if (BufferWireLayout != nullptr)
	{
		BufferWireLayout -> Bind();
	}
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
