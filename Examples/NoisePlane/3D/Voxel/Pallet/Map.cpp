#include "3D/Voxel/Pallet/Map.hpp"
#include "3D/Voxel/Pallet.hpp"
#include "3D/Voxel/Pallet/Geometry.hpp"
#include "3D/Voxel/Pallet/Geometry/Map.hpp"



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

VoxelPallet & VoxelPalletMap::New(const char * name, const VoxelPalletGeometry & geometry, VoxelMaterialType material)
{
	VoxelPalletIndex idx = Data.Count();
	Data.Insert(VoxelPallet(idx, name, geometry, material));
	return Data[idx];
}



#include "ValueType/Vector/U2.hpp"

#include "Texture/FileMap.hpp"

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
