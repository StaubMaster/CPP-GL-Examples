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

VoxelPallet & VoxelPalletMap::NewPallet(const char * name, const VoxelPalletGeometry & geometry, VoxelMaterialType material)
{
	VoxelPalletIndex idx = Data.Count();
	Data.Insert(VoxelPallet(idx, name, geometry, material));
	return Data[idx];
}

// do this in Context
#include "DirectoryInfo.hpp"
void VoxelPalletMap::Default(const DirectoryInfo & MediaDirectory)
{
	const VoxelPalletGeometry & cube_diag = VoxelPalletGeometry::CubeDiag;
	const VoxelPalletGeometry & cube_axis_Y = VoxelPalletGeometry::CubeAxisY;
	const VoxelPalletGeometry & axis_star = VoxelPalletGeometry::AxisStar;
	const VoxelPalletGeometry & cylinder = VoxelPalletGeometry::PrismY8;
	const VoxelPalletGeometry & slope = VoxelPalletGeometry::Slope;

	NewPallet("OrientationCube", cube_diag, VoxelMaterialType::None).TextureAxis(
		MediaDirectory.File("Images/Voxel/Orientation0/PrevX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevZ.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextZ.png")
	);
	NewPallet("OrientationAxisStar", axis_star, VoxelMaterialType::None).TextureAxis(
		MediaDirectory.File("Images/Voxel/Orientation0/PrevX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevZ.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextZ.png")
	);
	NewPallet("OrientationCylinder", cylinder, VoxelMaterialType::None).TextureAxis(
		MediaDirectory.File("Images/Voxel/Orientation0/PrevX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevZ.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextZ.png")
	);
	NewPallet("OrientationSlope", slope, VoxelMaterialType::None).TextureAxis(
		MediaDirectory.File("Images/Voxel/Orientation0/PrevX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/PrevZ.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextX.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextY.png"),
		MediaDirectory.File("Images/Voxel/Orientation0/NextZ.png")
	);

	NewPallet("DebugR", cube_diag, VoxelMaterialType::None).TextureAll(
		MediaDirectory.File("Images/Voxel/Debug/R.png")
	);
	NewPallet("DebugG", cube_diag, VoxelMaterialType::None).TextureAll(
		MediaDirectory.File("Images/Voxel/Debug/G.png")
	);
	NewPallet("DebugB", cube_diag, VoxelMaterialType::None).TextureAll(
		MediaDirectory.File("Images/Voxel/Debug/B.png")
	);

	NewPallet("Gray", cube_diag, VoxelMaterialType::Stone).TextureAll(
		MediaDirectory.File("Images/Voxel/Gray.png")
	);

	NewPallet("Grass", cube_diag, VoxelMaterialType::Dirt).TextureAll(
		MediaDirectory.File("Images/Voxel/Grass.png")
	);
	NewPallet("Dirt", cube_diag, VoxelMaterialType::Dirt).TextureAll(
		MediaDirectory.File("Images/Voxel/Dirt.png")
	);

	NewPallet("RedLog", cylinder, VoxelMaterialType::Wood).TexturePrismY(
		MediaDirectory.File("Images/Voxel/fancy_RedWood_Base.png"),
		MediaDirectory.File("Images/Voxel/fancy_RedWood_Belt.png")
	);
	NewPallet("Log", cube_axis_Y, VoxelMaterialType::Wood).TexturePrismY(
		MediaDirectory.File("Images/Voxel/Log_Base.png"),
		MediaDirectory.File("Images/Voxel/Log_Belt.png")
	);
	NewPallet("Leaves", cube_diag, VoxelMaterialType::None).TextureAll(
		MediaDirectory.File("Images/Voxel/Leave1.png")
	);

	NewPallet("Sand", cube_diag, VoxelMaterialType::Powder).TextureAll(
		MediaDirectory.File("Images/Voxel/Sand.png")
	);
	NewPallet("Snow", cube_diag, VoxelMaterialType::Powder).TextureAll(
		MediaDirectory.File("Images/Voxel/Snow.png")
	);
	NewPallet("Water", cube_diag, VoxelMaterialType::None).TextureAll(
		MediaDirectory.File("Images/Voxel/Water.png")
	);

	NewPallet("ConcreteCube", cube_diag, VoxelMaterialType::Stone).TextureAll(
		MediaDirectory.File("Images/Voxel/Concrete_0.png")
	);
	NewPallet("ConcreteCylinder", cylinder, VoxelMaterialType::Stone).TextureAll(
		MediaDirectory.File("Images/Voxel/Concrete_0.png")
	);
}



#include "ValueType/Vector/U2.hpp"

#include "TextureFileMap.hpp"

void VoxelPalletMap::TexturesAssign(TextureFileMap & tex_map)
{
	std::cout << "VoxelPalletMap::TexturesAssign() ....\n";
	for (unsigned int i = 0; i < Data.Count(); i++)
	{
		VoxelPallet & pallet = Data[i];
		for (unsigned int j = 0; j < 6; j++)
		{
			tex_map.Assign(pallet.Textures[j]);
		}
	}
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
