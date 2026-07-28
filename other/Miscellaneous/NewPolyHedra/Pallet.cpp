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
		if (Object -> Skin != nullptr)
		{
			Texture = Object -> Skin -> ToTexture();
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
			const PolyHedra::Corner & corner0 = Object -> Corners[face.idx[0]];
			const PolyHedra::Corner & corner1 = Object -> Corners[face.idx[1]];
			const PolyHedra::Corner & corner2 = Object -> Corners[face.idx[2]];

			data[c + 0].Position = corner0.Position;
			data[c + 1].Position = corner1.Position;
			data[c + 2].Position = corner2.Position;

			if (!Object -> UseCornerNormals)
			{
				data[c + 0].Normal = face.Normal;
				data[c + 1].Normal = face.Normal;
				data[c + 2].Normal = face.Normal;
			}
			else
			{
				data[c + 0].Normal = corner0.Normal;
				data[c + 1].Normal = corner1.Normal;
				data[c + 2].Normal = corner2.Normal;
			}
		}
	}

	for (unsigned int i = 0; i < data.Length(); i++)
	{
		data[i].Texture = VectorF3();
		data[i].Color = ColorF4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	if (Object -> Skin != nullptr)
	{
		const Skin & skin = *(Object -> Skin);
		for (unsigned int f = 0; f < skin.Faces.Count(); f++)
		{
			const Skin::Face & face = skin.Faces[f];
			for (unsigned int c = 0; c < 3; c++)
			{
				const Skin::Corner & corner = skin.Corners[face.idx[c]];
				unsigned int idx = (f * 3) + c;
				if (idx < data.Length())
				{
					data[idx].Texture.X = corner.Coord.X;
					data[idx].Texture.Y = corner.Coord.Y;
					data[idx].Texture.Z = corner.Index;
					data[idx].Color = corner.Color;
				}
			}
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
