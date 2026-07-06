#include "Pallet.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Data.hpp"
#include "PolyHedra/Skin/Skin.hpp"

#include "PolyHedra/Graphics/Full/Main/Data.hpp"
#include "PolyHedra/Graphics/Wire/Main/Data.hpp"

#include "Graphics/Buffer/VertexArray.hpp"



void NewPolyHedra_Pallet::Put()
{
	VertexArray::BindNone();
	if (Object != nullptr)
	{
		Object -> CalcNormals();
		{
			Container::Array<PolyHedraFull::Main::Data> data = Object -> ToMainData();
			BufferFull.DataFull(data.ToVoid());
			BufferFull.Count = data.Length();
		}
		{
			Container::Binary<PolyHedraWire::Main::Data> data;
			for (unsigned int i = 0; i < Object -> Corners.Count(); i++)
			{
				data.Insert(PolyHedraWire::Main::Data(Object -> Corners[i].Position, ColorF4(1, 1, 1)));
			}
			BufferWire.DataFull(data.ToVoid());
		}
		{
			BufferWireElem.DataFull(Object -> Edges.ToVoid());
		}
		Texture = Object -> Skins[0] -> ToTexture();
	}
}



NewPolyHedra_Pallet::~NewPolyHedra_Pallet()
{
	delete Object;
}
NewPolyHedra_Pallet::NewPolyHedra_Pallet(PolyHedra * object)
	: Object(object)
	, BufferFull(GL::BufferDataUsage::StaticDraw)
	, BufferWire(GL::BufferDataUsage::StaticDraw)
	, BufferWireElem(GL::BufferDataUsage::StaticDraw, GL::DrawIndexType::UnsignedInt)
	, BufferFullLayout(nullptr)
	, BufferWireLayout(nullptr)
	, Texture()
{ }



void NewPolyHedra_Pallet::GraphicsCreate()
{
	BufferFull.Create();
	BufferWire.Create();
	BufferWireElem.Create();
}
void NewPolyHedra_Pallet::GraphicsDelete()
{
	BufferFull.Delete();
	BufferWire.Delete();
	BufferWireElem.Delete();
}
