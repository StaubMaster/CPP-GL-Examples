#include "3D/StructureMap.hpp"
#include "3D/Structure.hpp"



StructureMap StructureMap::StaticMap;

#include <iostream>



Structure & StructureMap::operator[](const std::string & name)
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
	throw "StructureMap::operator[]";
}
const Structure & StructureMap::operator[](const std::string & name) const
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
	throw "StructureMap::operator[]";
}

Structure & StructureMap::New(const std::string & name)
{
	unsigned int idx = Data.Count();
	Structure structure;
	structure.Name = name;
	Data.Insert(structure);
	return Data[idx];
}
