#include "3D/Voxel/Pallet/Geometry/Map.hpp"
#include "3D/Voxel/Pallet/Geometry.hpp"



VoxelPalletGeometryMap VoxelPalletGeometryMap::StaticMap;

#include <string>
#include <iostream>

VoxelPalletGeometry & VoxelPalletGeometryMap::operator[](VoxelPalletGeometryIndex idx)
{
	return Data[idx];
}
const VoxelPalletGeometry & VoxelPalletGeometryMap::operator[](VoxelPalletGeometryIndex idx) const
{
	return Data[idx];
}

VoxelPalletGeometry & VoxelPalletGeometryMap::operator[](const char * name)
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
	throw "VoxelPalletGeometryMap::operator[]";
}
const VoxelPalletGeometry & VoxelPalletGeometryMap::operator[](const char * name) const
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
	throw "VoxelPalletGeometryMap::operator[]";
}

VoxelPalletGeometryIndex VoxelPalletGeometryMap::FindIndex(const char * name) const
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
VoxelPalletGeometryIndex VoxelPalletGeometryMap::FindIndex(const VoxelPalletGeometry * pallet) const
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
VoxelPalletGeometryIndex VoxelPalletGeometryMap::FindIndex(const VoxelPalletGeometry & pallet) const
{
	return FindIndex(&pallet);
}

VoxelPalletGeometry & VoxelPalletGeometryMap::New(const char * name)
{
	VoxelPalletGeometryIndex idx = Data.Count();
	VoxelPalletGeometry item;
	item.Name = name;
	Data.Insert(item);
	return Data[idx];
}
