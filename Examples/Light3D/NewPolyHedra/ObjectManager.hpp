#ifndef  NEW_POLYHEDRA_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_OBJECT_MANAGER_HPP

# include "Miscellaneous/Container/Binary.hpp"
# include "Graphics/Shader/Base.hpp"

struct NewPolyHedra_PalletObjectManager;
struct NewPolyHedra_PalletObjectData;

struct NewPolyHedra_ObjectManager
{
	Container::Binary<NewPolyHedra_PalletObjectManager*>	Managers;
	Container::Binary<NewPolyHedra_PalletObjectData*>		Objects;

	::Shader::Base	Shader; // Full and Wire

	void	InstancesClear();
	void	InstancesMake();
};

#endif