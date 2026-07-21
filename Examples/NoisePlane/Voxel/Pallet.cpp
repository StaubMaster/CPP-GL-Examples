#include "Pallet.hpp"
#include "GeometryPallet.hpp"
#include "Voxel.hpp"

#include "PolyHedra/Skin/Skin.hpp"



VoxelPallet::~VoxelPallet()
{ }
VoxelPallet::VoxelPallet()
	: Name(nullptr)
	, GeometryPallet(nullptr)
	, PolyHedra(nullptr)
	, Index(0xFFFF)
{ }
VoxelPallet::VoxelPallet(const char * name, const VoxelGeometryPallet & geometry_template, unsigned int idx)
	: Name(name)
	, GeometryPallet(&geometry_template)
	, PolyHedra(nullptr)
	, Index(idx)
{ }

VoxelPallet::VoxelPallet(const VoxelPallet & other)
	: Name(other.Name)
	, GeometryPallet(other.GeometryPallet)
	, PolyHedra(other.PolyHedra)
	, Index(other.Index)
{ }
VoxelPallet & VoxelPallet::operator=(const VoxelPallet & other)
{
	Name = other.Name;
	GeometryPallet = other.GeometryPallet;
	PolyHedra = other.PolyHedra;
	Index = other.Index;
	return *this;
}



void VoxelPallet::TextureAxis(
	FileInfo prevX, FileInfo prevY, FileInfo prevZ,
	FileInfo nextX, FileInfo nextY, FileInfo nextZ
)
{
	Textures[0].File = prevX; Textures[0].Index = -1;
	Textures[1].File = prevY; Textures[1].Index = -1;
	Textures[2].File = prevZ; Textures[2].Index = -1;
	Textures[3].File = nextX; Textures[3].Index = -1;
	Textures[4].File = nextY; Textures[4].Index = -1;
	Textures[5].File = nextZ; Textures[5].Index = -1;
}
void VoxelPallet::TextureAxis(
	FileInfo axisX, FileInfo axisY, FileInfo axisZ
)
{
	Textures[0].File = axisX; Textures[0].Index = -1;
	Textures[1].File = axisY; Textures[1].Index = -1;
	Textures[2].File = axisZ; Textures[2].Index = -1;
	Textures[3].File = axisX; Textures[3].Index = -1;
	Textures[4].File = axisY; Textures[4].Index = -1;
	Textures[5].File = axisZ; Textures[5].Index = -1;
}
void VoxelPallet::TexturePrismY(FileInfo base, FileInfo belt)
{
	Textures[0].File = belt; Textures[0].Index = -1;
	Textures[1].File = base; Textures[1].Index = -1;
	Textures[2].File = belt; Textures[2].Index = -1;
	Textures[3].File = belt; Textures[3].Index = -1;
	Textures[4].File = base; Textures[4].Index = -1;
	Textures[5].File = belt; Textures[5].Index = -1;
}
void VoxelPallet::TextureAll(FileInfo tex)
{
	Textures[0].File = tex; Textures[0].Index = -1;
	Textures[1].File = tex; Textures[1].Index = -1;
	Textures[2].File = tex; Textures[2].Index = -1;
	Textures[3].File = tex; Textures[3].Index = -1;
	Textures[4].File = tex; Textures[4].Index = -1;
	Textures[5].File = tex; Textures[5].Index = -1;
}

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Data.hpp"
#include "PolyHedra/Skin/Skin.hpp"
static void PolyHedraVoxelData(PolyHedra & polyhedra, const VoxelGeometryDataF::Face & data)
{
	Skin & skin = *(polyhedra.Skins[0]);
	VectorF3 off(0.5f);
	for (unsigned int i = 0; i < data.Data.Count(); i++)
	{
		const VoxelGraphicsDataF::Face & face = data.Data[i];

		unsigned int ph_i = polyhedra.Corners.Count();
		polyhedra.Insert_Corn(PolyHedra::Corner(face.Vertexes[0].Pos - off));
		polyhedra.Insert_Corn(PolyHedra::Corner(face.Vertexes[1].Pos - off));
		polyhedra.Insert_Corn(PolyHedra::Corner(face.Vertexes[2].Pos - off));
		polyhedra.Insert_Face3(ph_i + 0, ph_i + 1, ph_i + 2);

		skin.Insert_Face3(
			face.Vertexes[0].Tex,
			face.Vertexes[1].Tex,
			face.Vertexes[2].Tex
		);
	}
}
static void PolyHedraVoxelData(PolyHedra & polyhedra, const VoxelGeometryDataF::Full & voxel_graphics)
{
	PolyHedraVoxelData(polyhedra, voxel_graphics.Here);
	PolyHedraVoxelData(polyhedra, voxel_graphics.PrevX);
	PolyHedraVoxelData(polyhedra, voxel_graphics.PrevY);
	PolyHedraVoxelData(polyhedra, voxel_graphics.PrevZ);
	PolyHedraVoxelData(polyhedra, voxel_graphics.NextX);
	PolyHedraVoxelData(polyhedra, voxel_graphics.NextY);
	PolyHedraVoxelData(polyhedra, voxel_graphics.NextZ);
}
void VoxelPallet::MakePolyHedra()
{
	PolyHedra = new ::PolyHedra();
	Skin * skin = new ::Skin();
	skin -> Size = VectorU2(128, 64);
	for (unsigned int i = 0; i < 6; i++)
	{
		skin -> Images.Insert(Textures[i].File.LoadImage());
	}
	skin -> Done();
	PolyHedra -> Skins.Insert(skin);
	PolyHedraVoxelData(*PolyHedra, GeometryPallet -> GraphicsDataF);
}

Voxel VoxelPallet::ToVoxel() const
{
	Voxel voxel;
	//voxel.Pallet = VoxelPalletMap::All.FindIndex(this);
	voxel.Pallet = Index;
	return voxel;
}
Voxel VoxelPallet::ToVoxel(AxisRel placeAxis0, AxisRel placeAxis1) const
{
	Voxel voxel;
	//voxel.Pallet = VoxelPalletMap::All.FindIndex(this);
	voxel.Pallet = Index;
	voxel.Orientation = GeometryPallet -> Orient(placeAxis0, placeAxis1);
	return voxel;
}





VoxelPalletMap VoxelPalletMap::All;

#include <string>
#include <iostream>
VoxelPallet & VoxelPalletMap::operator[](unsigned short idx)
{
	return Data[idx];
}
const VoxelPallet & VoxelPalletMap::operator[](unsigned short idx) const
{
	return Data[idx];
}
VoxelPallet & VoxelPalletMap::operator[](const char * name)
{
	std::string str(name);
	for (unsigned int i = 0; i < Data.Count(); i++)
	{
		if (str == Data[i].Name)
		{
			return Data[i];
		}
	}
	std::cout << "not Found: " << name << '\n';
	for (unsigned int i = 0; i < Data.Count(); i++)
	{
		std::cout << ' ' << Data[i].Name << '\n';
	}
	throw "VoxelPalletMap::operator[]";
}
const VoxelPallet & VoxelPalletMap::operator[](const char * name) const
{
	std::string str(name);
	for (unsigned int i = 0; i < Data.Count(); i++)
	{
		if (str == Data[i].Name)
		{
			return Data[i];
		}
	}
	std::cout << "not Found: " << name << '\n';
	for (unsigned int i = 0; i < Data.Count(); i++)
	{
		std::cout << ' ' << Data[i].Name << '\n';
	}
	throw "VoxelPalletMap::operator[]";
}

unsigned short VoxelPalletMap::FindIndex(const char * name) const
{
	std::string str(name);
	for (unsigned int i = 0; i < Data.Count(); i++)
	{
		if (str == Data[i].Name)
		{
			return i;
		}
	}
	return 0xFFFF;
}
unsigned short VoxelPalletMap::FindIndex(const VoxelPallet * pallet) const
{
	for (unsigned int i = 0; i < Data.Count(); i++)
	{
		if (pallet == &Data[i])
		{
			return i;
		}
	}
	return 0xFFFF;
}
unsigned short VoxelPalletMap::FindIndex(const VoxelPallet & pallet) const
{
	return FindIndex(&pallet);
}

/*VoxelPallet * VoxelPalletMap::FindOrNull(const char * name)
{
	std::string str(name);
	for (unsigned int i = 0; i < Data.Count(); i++)
	{
		if (str == Data[i].Name)
		{
			return &Data[i];
		}
	}
	return nullptr;
}*/

#include "DirectoryInfo.hpp"
void VoxelPalletMap::Default(const DirectoryInfo & MediaDirectory)
{
	const VoxelGeometryPallet & cube = VoxelGeometryPallet::GeometryCube;
	const VoxelGeometryPallet & cylinder = VoxelGeometryPallet::GeometryCylinder;
	const VoxelGeometryPallet & slope = VoxelGeometryPallet::GeometrySlope;

	(void)cube;
	(void)cylinder;
	(void)slope;

	All.Data.Insert(VoxelPallet("DebugR", cube, All.Data.Count()));
	All.Data.Insert(VoxelPallet("DebugG", cube, All.Data.Count()));
	All.Data.Insert(VoxelPallet("DebugB", cube, All.Data.Count()));
	All.Data.Insert(VoxelPallet("OrientationCube", cube, All.Data.Count()));
	All.Data.Insert(VoxelPallet("OrientationCylinder", cylinder, All.Data.Count()));
//	All.Data.Insert(VoxelPallet("OrientationSlope", slope, All.Data.Count()));
	All.Data.Insert(VoxelPallet("Gray", cube, All.Data.Count()));
	All.Data.Insert(VoxelPallet("Grass", cube, All.Data.Count()));
	All.Data.Insert(VoxelPallet("Dirt", cube, All.Data.Count()));
	All.Data.Insert(VoxelPallet("RedLog", cylinder, All.Data.Count()));
	All.Data.Insert(VoxelPallet("Log", cube, All.Data.Count()));
	All.Data.Insert(VoxelPallet("Leaves", cube, All.Data.Count()));
	All.Data.Insert(VoxelPallet("Sand", cube, All.Data.Count()));
	All.Data.Insert(VoxelPallet("Snow", cube, All.Data.Count()));
	All.Data.Insert(VoxelPallet("Water", cube, All.Data.Count()));
	All.Data.Insert(VoxelPallet("ConcreteCube", cube, All.Data.Count()));
	All.Data.Insert(VoxelPallet("ConcreteCylinder", cylinder, All.Data.Count()));

	// JSON ?
	// or another specifici Parser ?
	All["DebugR"].TextureAll(MediaDirectory.File("Images/Voxel/Debug/R.png"));
	All["DebugG"].TextureAll(MediaDirectory.File("Images/Voxel/Debug/G.png"));
	All["DebugB"].TextureAll(MediaDirectory.File("Images/Voxel/Debug/B.png"));

	All["OrientationCube"].TextureAxis(
		MediaDirectory.File("Images/Voxel/Orientation0/PrevX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevZ.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextZ.png")
	);
	All["OrientationCylinder"].TextureAxis(
		MediaDirectory.File("Images/Voxel/Orientation0/PrevX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevZ.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextZ.png")
	);

	All["Gray"].TextureAll(MediaDirectory.File("Images/Voxel/Gray.png"));

	All["Grass"].TextureAll(MediaDirectory.File("Images/Voxel/Grass.png"));
	All["Dirt"].TextureAll(MediaDirectory.File("Images/Voxel/Dirt.png"));

	All["RedLog"].TexturePrismY(
		MediaDirectory.File("Images/Voxel/fancy_RedWood_Base.png"),
		MediaDirectory.File("Images/Voxel/fancy_RedWood_Belt.png")
	);

	All["Log"].TexturePrismY(
		MediaDirectory.File("Images/Voxel/Log_Base.png"),
		MediaDirectory.File("Images/Voxel/Log_Belt.png")
	);
	All["Leaves"].TextureAll(MediaDirectory.File("Images/Voxel/Leave1.png"));

	All["Sand"].TextureAll(MediaDirectory.File("Images/Voxel/Sand.png"));
	All["Snow"].TextureAll(MediaDirectory.File("Images/Voxel/Snow.png"));
	All["Water"].TextureAll(MediaDirectory.File("Images/Voxel/Water.png"));

	All["ConcreteCube"].TextureAll(MediaDirectory.File("Images/Voxel/Concrete_0.png"));
	All["ConcreteCylinder"].TextureAll(MediaDirectory.File("Images/Voxel/Concrete_0.png"));
}



#include "ValueType/Vector/U2.hpp"

#include "Chunk/Manager.hpp"

void VoxelPalletMap::LoadTextures(ChunkManager & manager)
{
	std::cout << "LoadTextures ....\n";
	Container::Binary<FileInfo> files;
	for (unsigned int i = 0; i < VoxelPalletMap::All.Data.Count(); i++)
	{
		for (unsigned int k = 0; k < 6; k++)
		{
			unsigned int j = 0xFFFFFFFF;
			for (unsigned int f = 0; f < files.Count(); f++)
			{
				if (files[f].Name() == (VoxelPalletMap::All.Data[i].Textures[k].File.Name()))
				{
					j = f;
					break;
				}
			}
			if (j == 0xFFFFFFFF)
			{
				j = files.Count();
				files.Insert(VoxelPalletMap::All.Data[i].Textures[k].File);
			}
			VoxelPalletMap::All.Data[i].Textures[k].Index = j;
		}
	}
	std::cout << "Textures: " << files.Count() << '\n';
	manager.Texture.Bind();
	manager.Texture.Assign(VectorU2(32, 32), files.ToArray());
	std::cout << "LoadTextures done\n";
}
void VoxelPalletMap::MakePolyHedra()
{
	std::cout << "MakePolyHedra ....\n";
	for (unsigned int i = 0; i < Data.Count(); i++)
	{
		Data[i].MakePolyHedra();
	}
	std::cout << "MakePolyHedra done\n";
}
