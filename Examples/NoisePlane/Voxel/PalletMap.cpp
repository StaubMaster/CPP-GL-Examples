#include "PalletMap.hpp"
#include "Pallet.hpp"
#include "PalletGeometry.hpp"



VoxelPalletMap VoxelPalletMap::StaticMap;

#include <string>
#include <iostream>
VoxelPallet & VoxelPalletMap::operator[](VoxelPalletIndex idx)
{
	return Data[idx];
}
const VoxelPallet & VoxelPalletMap::operator[](VoxelPalletIndex idx) const
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

VoxelPalletIndex VoxelPalletMap::FindIndex(const char * name) const
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
VoxelPalletIndex VoxelPalletMap::FindIndex(const VoxelPallet * pallet) const
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
VoxelPalletIndex VoxelPalletMap::FindIndex(const VoxelPallet & pallet) const
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
// do this in Context
VoxelPallet & VoxelPalletMap::NewPallet(const char * name, const VoxelPalletGeometry & geometry)
{
	VoxelPalletIndex idx = Data.Count();
	Data.Insert(VoxelPallet(name, geometry, idx));
	return Data[idx];
}
void VoxelPalletMap::Default(const DirectoryInfo & MediaDirectory)
{
	const VoxelPalletGeometry & cube = VoxelPalletGeometry::Cube;
	const VoxelPalletGeometry & cylinder = VoxelPalletGeometry::Cylinder;
	const VoxelPalletGeometry & slope = VoxelPalletGeometry::Slope;

	NewPallet("DebugR", cube).TextureAll(
		MediaDirectory.File("Images/Voxel/Debug/R.png")
	);
	NewPallet("DebugG", cube).TextureAll(
		MediaDirectory.File("Images/Voxel/Debug/G.png")
	);
	NewPallet("DebugB", cube).TextureAll(
		MediaDirectory.File("Images/Voxel/Debug/B.png")
	);

	NewPallet("OrientationCube", cube).TextureAxis(
		MediaDirectory.File("Images/Voxel/Orientation0/PrevX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevZ.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextZ.png")
	);
	NewPallet("OrientationCylinder", cylinder).TextureAxis(
		MediaDirectory.File("Images/Voxel/Orientation0/PrevX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevZ.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextZ.png")
	);
	NewPallet("OrientationSlope", slope).TextureAxis(
		MediaDirectory.File("Images/Voxel/Orientation0/PrevX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevZ.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextZ.png")
	);

	NewPallet("Gray", cube).TextureAll(
		MediaDirectory.File("Images/Voxel/Gray.png")
	);

	NewPallet("Grass", cube).TextureAll(
		MediaDirectory.File("Images/Voxel/Grass.png")
	);
	NewPallet("Dirt", cube).TextureAll(
		MediaDirectory.File("Images/Voxel/Dirt.png")
	);

	NewPallet("RedLog", cylinder).TexturePrismY(
		MediaDirectory.File("Images/Voxel/fancy_RedWood_Base.png"),
		MediaDirectory.File("Images/Voxel/fancy_RedWood_Belt.png")
	);
	NewPallet("Log", cube).TexturePrismY(
		MediaDirectory.File("Images/Voxel/Log_Base.png"),
		MediaDirectory.File("Images/Voxel/Log_Belt.png")
	);
	NewPallet("Leaves", cube).TextureAll(
		MediaDirectory.File("Images/Voxel/Leave1.png")
	);

	NewPallet("Sand", cube).TextureAll(
		MediaDirectory.File("Images/Voxel/Sand.png")
	);
	NewPallet("Snow", cube).TextureAll(
		MediaDirectory.File("Images/Voxel/Snow.png")
	);
	NewPallet("Water", cube).TextureAll(
		MediaDirectory.File("Images/Voxel/Water.png")
	);

	NewPallet("ConcreteCube", cube).TextureAll(
		MediaDirectory.File("Images/Voxel/Concrete_0.png")
	);
	NewPallet("ConcreteCylinder", cylinder).TextureAll(
		MediaDirectory.File("Images/Voxel/Concrete_0.png")
	);
}



#include "ValueType/Vector/U2.hpp"

#include "Chunk/Manager.hpp"

static unsigned short	FindFile(const Container::Binary<FileInfo> & files, const FileInfo & file)
{
	for (unsigned int i = 0; i < files.Count(); i++)
	{
		if (files[i].Name() == file.Name())
		{
			return i;
		}
	}
	return 0xFFFF;
}
static unsigned short	MakeFile(Container::Binary<FileInfo> & files, const FileInfo & file)
{
	unsigned short idx = files.Count();
	files.Insert(file);
	return idx;
}
static unsigned short	FindMakeFile(Container::Binary<FileInfo> & files, const FileInfo & file)
{
	unsigned short idx = FindFile(files, file);
	if (idx == 0xFFFF)
	{
		idx = MakeFile(files, file);
	}
	return idx;
}

void VoxelPalletMap::TexturesAssign(ChunkManager & manager)
{
	std::cout << "VoxelPalletMap::TexturesAssign() ....\n";
	Container::Binary<FileInfo> files;
	for (unsigned int i = 0; i < Data.Count(); i++)
	{
		VoxelPallet & pallet = Data[i];
		for (unsigned int k = 0; k < 6; k++)
		{
			TextureFileIndex & tex = pallet.Textures[k];
			tex.Index = FindMakeFile(files, tex.File);
		}
	}
	std::cout << "Textures: " << files.Count() << '\n';
	manager.Texture.Bind();
	manager.Texture.Assign(VectorU2(32, 32), files.ToArray());
	std::cout << "VoxelPalletMap::TexturesAssign() done\n";
}
void VoxelPalletMap::MakePolyHedras()
{
	std::cout << "VoxelPalletMap::MakePolyHedras() ....\n";
	for (unsigned int i = 0; i < Data.Count(); i++)
	{
		Data[i].MakePolyHedra();
	}
	std::cout << "VoxelPalletMap::MakePolyHedras() done\n";
}
