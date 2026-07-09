#ifndef  RAY_3D_HIT_HPP
# define RAY_3D_HIT_HPP

# include "Generics/Container/Array.hpp"

# include "ValueType/Ray/F3.hpp"
# include "ValueType/Ray/Hit/F3Type.hpp"



struct Trans3D;
class PolyHedra;

namespace NewPolyHedra
{
struct Pallet;
struct PalletObjectManager;

template<typename TypeData> struct Type_Object;
template<typename TypeData> struct Type_PalletObjectData;
};

// these use Trans.forward()
RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const Trans3D & trans);
RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const Trans3D & trans, float scale);

// check Bounding Box
// should that be stored in PolyHedra of Pallet

template<typename TypeData> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const TypeData & data);
template<typename TypeData> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Pallet & pallet, const TypeData & data);
template<typename TypeData> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::PalletObjectManager & manager, const TypeData & data);
template<typename TypeData> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Type_Object<TypeData> & object);
template<typename TypeData> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Type_PalletObjectData<TypeData> & object);

#endif