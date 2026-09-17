#ifndef  NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_INIT_HPP
# define NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_INIT_HPP

namespace NewPolyHedra
{
template<typename TypeData, typename TypeInstanceData>
struct Type_ObjectManager;

namespace Basic3D
{

struct ObjectData;
struct InstanceData;
typedef Type_ObjectManager<ObjectData, InstanceData> ObjectManager;

void	Create(ObjectManager & manager);
void	Delete(ObjectManager & manager);
};
};

#endif