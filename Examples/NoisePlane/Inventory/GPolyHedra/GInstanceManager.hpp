#ifndef  G_POLYHEDRA_INSTANCE_MANAGER_HPP
# define G_POLYHEDRA_INSTANCE_MANAGER_HPP

# include "GPolyHedra/Graphics/Full/Buffer.hpp"
# include "GPolyHedra/Graphics/Wire/Buffer.hpp"

# include "Graphics/Texture/Array2D.hpp"

# include "Miscellaneous/Container/Binary.hpp"
# include "Instance/Basic3D/Data.hpp"

class PolyHedra;
struct PolyHedraObjectData;

template <typename InstDataType>
struct GPolyHedraInstanceManager
{
::PolyHedra *	PolyHedra;

// Object Defaults
bool	DefaultFullVisibility;
bool	DefaultWireVisibility;

// put Flags into Buffers ?
// store a Container of Data in Buffer ?
// Main Data needs to be put into Buffers
bool	UpdateFullMain;
bool	UpdateWireMain;
// Attributes in Buffers need to be initialized
bool	UpdateFullInit;
bool	UpdateWireInit;

bool						GraphicsExist;
::PolyHedraFull::Buffer		BufferFull;
::PolyHedraWire::Buffer		BufferWire;
Texture::Array2D			Texture;

Container::Binary<InstDataType>	InstancesFull;
Container::Binary<InstDataType>	InstancesWire;

~GPolyHedraInstanceManager() { }
GPolyHedraInstanceManager()
	: PolyHedra(nullptr)
	, DefaultFullVisibility(true)
	, DefaultWireVisibility(false)
	, UpdateFullMain(false)
	, UpdateWireMain(false)
	, UpdateFullInit(false)
	, UpdateWireInit(false)
	, GraphicsExist(false)
	, BufferFull()
	, BufferWire()
	, Texture()
	, InstancesFull()
	, InstancesWire()
{ }
GPolyHedraInstanceManager(const GPolyHedraInstanceManager & other)
	: PolyHedra(other.PolyHedra)
	, DefaultFullVisibility(other.DefaultFullVisibility)
	, DefaultWireVisibility(other.DefaultWireVisibility)
	, UpdateFullMain(other.UpdateFullMain)
	, UpdateWireMain(other.UpdateWireMain)
	, UpdateFullInit(other.UpdateFullInit)
	, UpdateWireInit(other.UpdateWireInit)
	, GraphicsExist(other.GraphicsExist)
	, BufferFull(other.BufferFull)
	, BufferWire(other.BufferWire)
	, Texture(other.Texture)
	, InstancesFull()
	, InstancesWire()
{ }
GPolyHedraInstanceManager & operator=(const GPolyHedraInstanceManager & other)
{
	PolyHedra = other.PolyHedra;
	DefaultFullVisibility = other.DefaultFullVisibility;
	DefaultWireVisibility = other.DefaultWireVisibility;
	UpdateFullMain = other.UpdateFullMain;
	UpdateWireMain = other.UpdateWireMain;
	UpdateFullInit = other.UpdateFullInit;
	UpdateWireInit = other.UpdateWireInit;
	GraphicsExist = other.GraphicsExist;
	BufferFull = other.BufferFull;
	BufferWire = other.BufferWire;
	Texture = other.Texture;
	InstancesFull.Clear();
	InstancesWire.Clear();
	return *this;
}

GPolyHedraInstanceManager(::PolyHedra * polyhedra)
	: PolyHedra(polyhedra)
	, UpdateFullMain(true)
	, UpdateWireMain(true)
	, UpdateFullInit(false)
	, UpdateWireInit(false)
	, GraphicsExist(false)
	, BufferFull()
	, BufferWire()
	, InstancesFull()
	, InstancesWire()
{ }
void Change(::PolyHedra * polyhedra)
{
	PolyHedra = polyhedra;
	UpdateFullMain = true;
	UpdateWireMain = true;
}



void GraphicsCreate()
{
	if (!GraphicsExist)
	{
		BufferFull.Create();
		BufferWire.Create();
		GraphicsExist = true;
		UpdateFullInit = true;
		UpdateWireInit = true;
	}
}
void GraphicsDelete()
{
	if (GraphicsExist)
	{
		BufferFull.Delete();
		BufferWire.Delete();
		GraphicsExist = false;
	}
}



void UpdateFullBufferInit()
{
	if (!(UpdateFullInit && GraphicsExist)) { return; }

	BufferFull.Main.Init();
	BufferFull.Inst.Init();

	UpdateFullInit = false;
}
void UpdateFullBufferMain()
{
	if (!(UpdateFullMain && PolyHedra != nullptr && GraphicsExist)) { return; }

	{
		Container::Pointer<PolyHedraFull::Main::Data> data = PolyHedra -> ToMainData();
		BufferFull.Main.Change(data);
		data.Delete();
	}

	if (PolyHedra -> Skin != NULL)
	{
		//_Texture = _PolyHedra -> Skin -> ToTexture();
		Skin2DA * skin = (Skin2DA*)(PolyHedra -> Skin);
		//skin -> ToTexture(Buffer.Texture);
		skin -> ToTexture(Texture);
	}
	else
	{
		//_Texture = NULL;
		//Buffer.Texture.Delete();
		Texture.Delete();
	}

	UpdateFullMain = false;
}
void UpdateFullBufferInst()
{
	BufferFull.Inst.Change(InstancesFull);
}
void DrawFull()
{
	UpdateFullBufferInit();
	UpdateFullBufferMain();
	UpdateFullBufferInst();
	Texture.Bind();
	BufferFull.Draw();
}

void UpdateWireBufferInit()
{
	if (!(UpdateWireInit && GraphicsExist)) { return; }

	BufferWire.Main.Init();
	BufferWire.Inst.Init();

	UpdateWireInit = false;
}
void UpdateWireBufferMain()
{
	if (!(UpdateWireMain && PolyHedra != nullptr && GraphicsExist)) { return; }

	{
		Container::Binary<PolyHedraWire::Main::Data> data;
		for (unsigned int i = 0; i < PolyHedra -> Corners.Count(); i++)
		{
			data.Insert(PolyHedraWire::Main::Data(PolyHedra -> Corners[i].Position, ColorF4(1, 1, 1)));
		}
		BufferWire.Main.Change(data);
	}
	{
		/*Container::Binary<PolyHedra::Edge> data;
		for (unsigned int i = 0; i < PolyHedra -> Faces.Count(); i++)
		{
			const PolyHedra::Face & face = PolyHedra -> Faces[i];
			if (face.Check(PolyHedra -> Corners.Count()))
			{
				data.Insert(PolyHedra::Edge(face.udx[0], face.udx[1]));
				data.Insert(PolyHedra::Edge(face.udx[1], face.udx[2]));
				data.Insert(PolyHedra::Edge(face.udx[2], face.udx[0]));
			}
		}
		BufferWire.Elem.Change(data);*/
		BufferWire.Elem.Change(PolyHedra -> Edges);
	}

	UpdateWireMain = false;
}
void UpdateWireBufferInst()
{
	BufferWire.Inst.Change(InstancesWire);
}
void DrawWire()
{
	UpdateWireBufferInit();
	UpdateWireBufferMain();
	UpdateWireBufferInst();
	BufferWire.Draw();
}



void ClearInstances()
{
	InstancesFull.Clear();
	InstancesWire.Clear();
}
void PlaceInstance(const PolyHedraObjectData & obj)
{
	if (obj.PolyHedra == PolyHedra)
	{
		if (obj.DrawFull)
		{
			InstancesFull.Insert(Instance::Basic3D::Data(obj.Trans));
		}
		if (obj.DrawWire)
		{
			InstancesWire.Insert(Instance::Basic3D::Data(obj.Trans));
		}
	}
}
void PlaceInstances(const Container::Member<PolyHedraObjectData> & objs)
{
	for (unsigned int i = 0; i < objs.Count(); i++)
	{
		PlaceInstance(objs[i]);
	}
}

};

#endif