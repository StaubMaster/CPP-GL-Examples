#ifndef  NEW_POLYHEDRA_TYPE_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_OBJECT_MANAGER_HPP

# include "ObjectManager.hpp"

template<
	typename TypeShaderLayout,
	typename TypeBufferLayout
>
struct NewPolyHedra_Type_ObjectManager : public NewPolyHedra_ObjectManager
{
	TypeShaderLayout	ShaderLayout; // Full and Wire
	TypeBufferLayout	BufferLayout; // Full and Wire
};

#endif