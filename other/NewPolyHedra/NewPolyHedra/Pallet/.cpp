#include "NewPolyHedra/Pallet/.hpp"

#include "PolyHedra/.hpp"

#include "NewPolyHedra/Pallet/Full/Data.hpp"
#include "NewPolyHedra/Pallet/Wire/Data.hpp"

#include "Graphics/VertexArray/Base.hpp"
#include "Graphics/Attribute/General/Layout.hpp"



bool NewPolyHedra::Pallet::Equals(const PolyHedra * polyhedra) const	{ return Object == polyhedra; }
bool NewPolyHedra::Pallet::Equals(const PolyHedra & polyhedra) const	{ return Object == &polyhedra; }

//bool NewPolyHedra::Pallet::Equals(const std::string & name) const		{ return Name == name; }
//bool NewPolyHedra::Pallet::Equals(const char * name) const				{ return Name == name; }



NewPolyHedra::Pallet::~Pallet()
{
	delete Object;
}
NewPolyHedra::Pallet::Pallet()
	: Object(nullptr)
	//, Name()
	, BufferFull(GL::BufferDataUsage::StaticDraw)
	, BufferWire(GL::BufferDataUsage::StaticDraw)
	, BufferWireElem(GL::BufferDataUsage::StaticDraw, GL::DrawIndexType::UnsignedInt)
	, Texture()
{ }
NewPolyHedra::Pallet::Pallet(PolyHedra * object)
	: Object(object)
	//, Name()
	, BufferFull(GL::BufferDataUsage::StaticDraw)
	, BufferWire(GL::BufferDataUsage::StaticDraw)
	, BufferWireElem(GL::BufferDataUsage::StaticDraw, GL::DrawIndexType::UnsignedInt)
	, Texture()
{ }
/*NewPolyHedra::Pallet::Pallet(PolyHedra * object, std::string name)
	: Object(object)
	, Name(name)
	, BufferFull(GL::BufferDataUsage::StaticDraw)
	, BufferWire(GL::BufferDataUsage::StaticDraw)
	, BufferWireElem(GL::BufferDataUsage::StaticDraw, GL::DrawIndexType::UnsignedInt)
	, Texture()
{ }*/



void NewPolyHedra::Pallet::GraphicsPut()
{
	VertexArray::Base::BindNone();
	if (Object != nullptr)
	{
		GraphicsPutFull();
		GraphicsPutWire();
		/*if (Object -> Skin != nullptr)
		{
			Texture = Object -> Skin -> ToTexture();
		}*/
		Texture = Object -> Skin.ToTexture();
	}
}
void NewPolyHedra::Pallet::GraphicsPutFull()
{
	Container::Array<PalletFull::Triangle> data(Object -> Flesh.Faces.Count());

	for (unsigned int i = 0; i < Object -> Flesh.Faces.Count(); i++)
	{
		const PolyHedraFlesh::Face & face = Object -> Flesh.Faces[i];
		if (face.Check(Object -> Flesh.Corners.Count()))
		{
			PalletFull::Triangle & tri = data[i];

			const PolyHedraFlesh::Corner & corner0 = Object -> Flesh.Corners[face.idx[0]];
			const PolyHedraFlesh::Corner & corner1 = Object -> Flesh.Corners[face.idx[1]];
			const PolyHedraFlesh::Corner & corner2 = Object -> Flesh.Corners[face.idx[2]];

			PalletFull::Vertex & vert0 = tri.Data[0];
			PalletFull::Vertex & vert1 = tri.Data[1];
			PalletFull::Vertex & vert2 = tri.Data[2];

			vert0.Position = corner0.Position;
			vert1.Position = corner1.Position;
			vert2.Position = corner2.Position;

			if (face.NormalGroup == 0xFFFFFFFF)
			{
				vert0.Normal = face.Normal;
				vert1.Normal = face.Normal;
				vert2.Normal = face.Normal;
			}
			else
			{
				vert0.Normal = VectorF3();
				vert1.Normal = VectorF3();
				vert2.Normal = VectorF3();
			}
		}
	}

	// Normals (unoptimized)
	unsigned int normal_group_limit = 0xFFFFFFFF;
	for (unsigned int i = 0; i < Object -> Flesh.Faces.Count(); i++)
	{
		const PolyHedraFlesh::Face & face = Object -> Flesh.Faces[i];
		if (face.NormalGroup != 0xFFFFFFFF)
		{
			if (normal_group_limit == 0xFFFFFFFF || face.NormalGroup > normal_group_limit)
			{
				normal_group_limit = face.NormalGroup;
			}
		}
	}
	if (normal_group_limit != 0xFFFFFFFF)
	{
		Container::Array<VectorF3> normals(Object -> Flesh.Corners.Count());
		for (unsigned int normal_group = 0; normal_group <= normal_group_limit; normal_group++)
		{
			for (unsigned int i = 0; i < normals.Length(); i++)
			{
				normals[i] = VectorF3();
			}
			for (unsigned int i = 0; i < Object -> Flesh.Faces.Count(); i++)
			{
				const PolyHedraFlesh::Face & face = Object -> Flesh.Faces[i];
				if (face.NormalGroup == normal_group)
				{
					if (face.Check(normals.Length()))
					{
						normals[face.idx[0]] += face.Normal;
						normals[face.idx[1]] += face.Normal;
						normals[face.idx[2]] += face.Normal;
					}
				}
			}
			for (unsigned int i = 0; i < normals.Length(); i++)
			{
				normals[i] = normals[i].normalize();
			}
			for (unsigned int i = 0; i < Object -> Flesh.Faces.Count(); i++)
			{
				const PolyHedraFlesh::Face & face = Object -> Flesh.Faces[i];
				if (face.NormalGroup == normal_group)
				{
					PalletFull::Triangle & tri = data[i];
					PalletFull::Vertex & vert0 = tri.Data[0];
					PalletFull::Vertex & vert1 = tri.Data[1];
					PalletFull::Vertex & vert2 = tri.Data[2];
					vert0.Normal = normals[face.idx[0]];
					vert1.Normal = normals[face.idx[1]];
					vert2.Normal = normals[face.idx[2]];
				}
			}
		}
	}

	//if (Object -> Skin != nullptr)
	{
		//const Skin & skin = *(Object -> Skin);
		const PolyHedraSkin & skin = (Object -> Skin);
		for (unsigned int i = 0; i < data.Length(); i++)
		{
			PalletFull::Triangle & tri = data[i];
			for (unsigned int j = 0; j < 3; j++)
			{
				PalletFull::Vertex & vert = tri.Data[j];
				vert.Texture = VectorF3();
				vert.Color = skin.Color;
			}
		}
		for (unsigned int i = 0; i < skin.Faces.Count(); i++)
		{
			const PolyHedraSkin::Face & face = skin.Faces[i];
			if (i < data.Length())
			{
				PalletFull::Triangle & tri = data[i];
				for (unsigned int j = 0; j < 3; j++)
				{
					const PolyHedraSkin::Corner & corner = skin.Corners[face.idx[j]];
					PalletFull::Vertex & vert = tri.Data[j];
					vert.Texture.X = corner.Coord.X;
					vert.Texture.Y = corner.Coord.Y;
					vert.Texture.Z = corner.Index;
					vert.Color = corner.Color;
				}
			}
		}
	}
	/*else
	{
		for (unsigned int i = 0; i < data.Length(); i++)
		{
			PalletFull::Triangle & tri = data[i];
			for (unsigned int j = 0; j < 3; j++)
			{
				PalletFull::Vertex & vert = tri.Data[j];
				vert.Texture = VectorF3();
				vert.Color = ColorF4(1.0f, 1.0f, 1.0f, 1.0f);;
			}
		}
	}*/

	BufferFull.DataFull(data.ToVoid());
	BufferFull.Count = data.Length() * 3;
}
void NewPolyHedra::Pallet::GraphicsPutWire()
{
	{
		Container::Array<PalletWire::Data> data(Object -> Flesh.Corners.Count());
		for (unsigned int i = 0; i < Object -> Flesh.Corners.Count(); i++)
		{
			//data[i] = PalletWireData(Object -> Corners[i].Position, ColorF4(1, 1, 1));
			data[i].Pos = Object -> Flesh.Corners[i].Position;
			data[i].Col = ColorF4(1, 1, 1);
		}
		BufferWire.DataFull(data.ToVoid());
		BufferWire.Count = data.Length();
	}

	{
		Container::Array<PolyHedraFlesh::Edge> data = Object -> Flesh.Edges.ToArray();
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
