#include "Pallet.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Skin/Skin.hpp"
#include "PolyHedra/Graphics/Full/Main/Data.hpp"

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
	, BufferFullLayout(nullptr)
	, BufferWireLayout(nullptr)
	, Texture()
{ }



void NewPolyHedra_Pallet::GraphicsCreate()
{
	BufferFull.Create();
	BufferWire.Create();
}
void NewPolyHedra_Pallet::GraphicsDelete()
{
	BufferFull.Delete();
	BufferWire.Delete();
}
