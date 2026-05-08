#include "VoxelPallet.hpp"
#include "VoxelOrientation.hpp"
#include "Voxel.hpp"

#include "VoxelGeometryPallet.hpp"



VoxelPallet::~VoxelPallet()
{ }
VoxelPallet::VoxelPallet()
	: Name(nullptr)
	, GeometryPallet(nullptr)
	, PolyHedra(nullptr)
{ }
VoxelPallet::VoxelPallet(const char * name, const VoxelGeometryPallet & geometry_template)
	: Name(name)
	, GeometryPallet(&geometry_template)
	, PolyHedra(nullptr)
{ }

VoxelPallet::VoxelPallet(const VoxelPallet & other)
	: Name(other.Name)
	, GeometryPallet(other.GeometryPallet)
	, PolyHedra(nullptr)
{ }
VoxelPallet & VoxelPallet::operator=(const VoxelPallet & other)
{
	Name = other.Name;
	GeometryPallet = other.GeometryPallet;
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
#include "PolyHedra/Skin/Skin2DA.hpp"
static void PolyHedraVoxelData(PolyHedra & polyhedra, const VoxelAxisGraphicsData & data)
{
	Skin2DA & skin = *((Skin2DA*)polyhedra.Skin);
	VectorF3 off(0.5f);
	for (unsigned int i = 0; i < data.Data.Count(); i++)
	{
		const VoxelGraphics::MainTriangle & face = data.Data[i];

		unsigned int ph_i = polyhedra.Corners.Count();
		polyhedra.Insert_Corn(PolyHedra::Corner(face.Corners[0].Pos - off));
		polyhedra.Insert_Corn(PolyHedra::Corner(face.Corners[1].Pos - off));
		polyhedra.Insert_Corn(PolyHedra::Corner(face.Corners[2].Pos - off));
		polyhedra.Insert_Face3(ph_i + 0, ph_i + 1, ph_i + 2);

		skin.Insert_Face3(
			Skin2DFaceCorner(face.Corners[0].Tex),
			Skin2DFaceCorner(face.Corners[1].Tex),
			Skin2DFaceCorner(face.Corners[2].Tex)
		);
	}
}
static void PolyHedraVoxelData(PolyHedra & polyhedra, const VoxelGraphicsData & voxel_graphics)
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
	PolyHedra -> Skin = new Skin2DA();
	Skin2DA & skin = *((Skin2DA*)PolyHedra -> Skin);
	skin.W = 128;
	skin.H = 64;
	for (unsigned int i = 0; i < 6; i++)
	{
		skin.Images.Insert(Textures[i].File.LoadImage());
	}
	skin.Done();
	PolyHedraVoxelData(*PolyHedra, GeometryPallet -> Data);
}

Voxel VoxelPallet::ToVoxel(AxisRel placeAxis0, AxisRel placeAxis1) const
{
	Voxel voxel;
	voxel.Pallet = this;
	voxel.Orientation = GeometryPallet -> Orient(placeAxis0, placeAxis1);
	return voxel;
}





VoxelPalletMap VoxelPalletMap::All;

#include <string>
#include <iostream>
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
bool VoxelPalletMap::Contains(const char * name) const
{
	std::string str(name);
	for (unsigned int i = 0; i < Data.Count(); i++)
	{
		if (str == Data[i].Name)
		{
			return true;
		}
	}
	return false;
}
VoxelPallet * VoxelPalletMap::FindOrNull(const char * name)
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
}

#include "DirectoryInfo.hpp"
void VoxelPalletMap::Default(const DirectoryInfo & MediaDirectory)
{
	VoxelPalletMap::All.Data.Insert(VoxelPallet("OrientationCube", VoxelGeometryPallet::Cube));
	VoxelPalletMap::All.Data.Insert(VoxelPallet("OrientationCylinder", VoxelGeometryPallet::Cylinder));
//	VoxelPalletMap::All.Data.Insert(VoxelPallet("OrientationSlope", VoxelGeometryPallet::Slope));
	VoxelPalletMap::All.Data.Insert(VoxelPallet("Gray", VoxelGeometryPallet::Cube));
	VoxelPalletMap::All.Data.Insert(VoxelPallet("Grass", VoxelGeometryPallet::Cube));
	VoxelPalletMap::All.Data.Insert(VoxelPallet("RedLog", VoxelGeometryPallet::Cylinder));
	VoxelPalletMap::All.Data.Insert(VoxelPallet("Sand", VoxelGeometryPallet::Cube));
	VoxelPalletMap::All.Data.Insert(VoxelPallet("Snow", VoxelGeometryPallet::Cube));
	VoxelPalletMap::All.Data.Insert(VoxelPallet("Water", VoxelGeometryPallet::Cube));
	VoxelPalletMap::All.Data.Insert(VoxelPallet("ConcreteCube", VoxelGeometryPallet::Cube));
	VoxelPalletMap::All.Data.Insert(VoxelPallet("ConcreteCylinder", VoxelGeometryPallet::Cylinder));

	// JSON ?
	// or another specifici Parser ?

	VoxelPalletMap::All["OrientationCube"].TextureAxis(
		MediaDirectory.File("Images/Voxel/Orientation0/PrevX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevZ.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextZ.png")
	);
	VoxelPalletMap::All["OrientationCylinder"].TextureAxis(
		MediaDirectory.File("Images/Voxel/Orientation0/PrevX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevZ.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextZ.png")
	);

	VoxelPalletMap::All["Gray"].TextureAll(MediaDirectory.File("Images/Voxel/Gray.png"));

	// loading Dirt.png instead of Grass.png breaks all PNGs, including the Font ???
	//VoxelPalletMap::All["Grass"].TextureAll(MediaDirectory.File("Images/Voxel/Dirt.png"));
	VoxelPalletMap::All["Grass"].TextureAll(MediaDirectory.File("Images/Voxel/Grass.png"));

	VoxelPalletMap::All["RedLog"].TexturePrismY(
		MediaDirectory.File("Images/Voxel/fancy_RedWood_Base.png"),
		MediaDirectory.File("Images/Voxel/fancy_RedWood_Belt.png")
	);

	/*
		Sand.png dosent load properly. fix that
		And uses static Huffman Block
		currently PNGs only work with Dynamic Huffman
		turn off PNG: Unknown Type:
	*/
	VoxelPalletMap::All["Sand"].TextureAll(MediaDirectory.File("Images/Voxel/Sand.png"));
	VoxelPalletMap::All["Snow"].TextureAll(MediaDirectory.File("Images/Voxel/Snow.png"));
	VoxelPalletMap::All["Water"].TextureAll(MediaDirectory.File("Images/Voxel/Water.png"));

	VoxelPalletMap::All["ConcreteCube"].TextureAll(MediaDirectory.File("Images/Voxel/Concrete_0.png"));
	VoxelPalletMap::All["ConcreteCylinder"].TextureAll(MediaDirectory.File("Images/Voxel/Concrete_0.png"));
}
#include "ValueType/VectorU2.hpp"
#include "ChunkManager.hpp"
void VoxelPalletMap::LoadTextures(ChunkManager & manager)
{
		manager.Texture.Bind();
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
						j = f; break;
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
		manager.Texture.Assign(VectorU2(32, 32), files);
}
void VoxelPalletMap::MakePolyHedra()
{
	for (unsigned int i = 0; i < Data.Count(); i++)
	{
		Data[i].MakePolyHedra();
	}
}
