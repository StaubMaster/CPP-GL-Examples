#include "Pallet.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Data.hpp"
#include "PolyHedra/Skin/Skin.hpp"
#include "PolyHedra/Skin/Data.hpp"

#include "NewPolyHedra/Pallet/Full/Data.hpp"
#include "NewPolyHedra/Pallet/Wire/Data.hpp"

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
		GraphicsPutFull();
		GraphicsPutWire();
		// why is this hardcoded to allways use Skins[0] ?
		if (Object -> Skins.Count() != 0)
		{
			Texture = Object -> Skins[0] -> ToTexture();
		}
	}
}
void NewPolyHedra::Pallet::GraphicsPutFull()
{
	Container::Array<PalletFull::Data> data(Object -> Faces.Count() * 3);

	for (unsigned int f = 0; f < Object -> Faces.Count(); f++)
	{
		int c = f * 3;
		const PolyHedra::Face & face = Object -> Faces[f];
		if (face.Check(Object -> Corners.Count()))
		{
			const PolyHedra::Corner & cornerX = Object -> Corners[face.udx[0]];
			const PolyHedra::Corner & cornerY = Object -> Corners[face.udx[1]];
			const PolyHedra::Corner & cornerZ = Object -> Corners[face.udx[2]];

			data[c + 0].Position = cornerX.Position;
			data[c + 1].Position = cornerY.Position;
			data[c + 2].Position = cornerZ.Position;

			if (!Object -> UseCornerNormals)
			{
				data[c + 0].Normal = face.Normal;
				data[c + 1].Normal = face.Normal;
				data[c + 2].Normal = face.Normal;
			}
			else
			{
				data[c + 0].Normal = cornerX.Normal;
				data[c + 1].Normal = cornerY.Normal;
				data[c + 2].Normal = cornerZ.Normal;
			}
		}
		else
		{
			//std::cout << "Invalid Face\n";
		}
	}

	// why is this hardcoded to allways use Skins[0] ?
	if (Object -> Skins.Count() == 0)
	{
		for (unsigned int i = 0; i < data.Length(); i++)
		{
			data[i].Texture = VectorF3();
		}
	}
	else
	{
		const Skin * skin = Object -> Skins[0];
		for (unsigned int f = 0; f < skin -> Faces.Count(); f++)
		{
			int c = f * 3;
			const Skin::Face & face = skin -> Faces[f];
			data[c + 0].Texture = face.Corner[0];
			data[c + 1].Texture = face.Corner[1];
			data[c + 2].Texture = face.Corner[2];
		}
	}

	BufferFull.DataFull(data.ToVoid());
	BufferFull.Count = data.Length();
}
void NewPolyHedra::Pallet::GraphicsPutWire()
{
	{
		Container::Array<PalletWire::Data> data(Object -> Corners.Count());
		for (unsigned int i = 0; i < Object -> Corners.Count(); i++)
		{
			//data[i] = PalletWireData(Object -> Corners[i].Position, ColorF4(1, 1, 1));
			data[i].Pos = Object -> Corners[i].Position;
			data[i].Col = ColorF4(1, 1, 1);
		}
		BufferWire.DataFull(data.ToVoid());
		BufferWire.Count = data.Length();
	}

	{
		Container::Array<PolyHedra::Edge> data = Object -> Edges.ToArray();
		BufferWireElem.DataFull(data.ToVoid());
		BufferWireElem.Count = data.Length() * 2;
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
