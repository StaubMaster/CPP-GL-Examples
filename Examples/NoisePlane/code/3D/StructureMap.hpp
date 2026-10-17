#ifndef  STRUCTURE_MAP_HPP
# define STRUCTURE_MAP_HPP

# include "Generics/Container/Binary.hpp"

struct Structure;

# include <string>

struct StructureMap
{
	static StructureMap	StaticMap;

	Container::Binary<Structure>	Data;

	Structure &				operator[](const std::string & name);
	const Structure &		operator[](const std::string & name) const;

	Structure &		New(const std::string & name);
};

#endif