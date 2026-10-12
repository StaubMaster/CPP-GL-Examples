#ifndef  NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_INIT_HPP
# define NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_INIT_HPP

namespace NewPolyHedra
{
template<typename TypeData, typename TypeInstanceData> struct TypeManager;

namespace Basic3D
{
typedef ObjectData TypeData;
typedef InstanceData TypeInstanceData;
typedef NewPolyHedra::TypeManager		<TypeData, TypeInstanceData> TypeManager;

void	Create(TypeManager & manager);
void	Delete(TypeManager & manager);
};
};

#endif