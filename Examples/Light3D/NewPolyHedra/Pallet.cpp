#include "Pallet.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Skin/Skin.hpp"
#include "PolyHedra/Graphics/Full/Main/Data.hpp"

#include "Graphics/Buffer/VertexArray.hpp"




bool NewPolyHedra_Pallet::Is(PolyHedra * object) const
{
	return (Object == object);
}



NewPolyHedra_Pallet::~NewPolyHedra_Pallet()
{
	delete Object;
}
NewPolyHedra_Pallet::NewPolyHedra_Pallet(PolyHedra * object)
	: Object(object)
	, Buffer(GL::BufferDataUsage::StaticDraw)
	, Texture()
	, Layout(nullptr)
{ }



void NewPolyHedra_Pallet::Put()
{
	VertexArray::BindNone();
	if (Object != nullptr)
	{
		Object -> CalcNormals();
		Container::Array<PolyHedraFull::Main::Data> data = Object -> ToMainData();
		Buffer.DataFull(data.ToVoid());
		Buffer.Count = data.Length();
		Texture = Object -> Skins[0] -> ToTexture();
	}
}



void NewPolyHedra_Pallet::GraphicsCreate()
{
	Buffer.Create();
}
void NewPolyHedra_Pallet::GraphicsDelete()
{
	Buffer.Delete();
}
