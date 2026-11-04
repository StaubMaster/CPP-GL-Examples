#ifndef  RAY_3D_HIT_HPP
# define RAY_3D_HIT_HPP

# include "ValueType/Ray/F3.hpp"
# include "ValueType/Ray/Hit/F3Type.hpp"

typedef RayHitF3Type<unsigned int> RayHitReturn;



struct Trans3D;
class PolyHedra;

namespace NewPolyHedra
{
struct Pallet;
struct BaseDisplayObject;
template<typename TypeLogicalData> struct TypeLogicalObject;
template<typename TypeLogicalData> struct TypeObject;
};

// these use Trans.forward()
RayHitReturn RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const Trans3D & trans);
RayHitReturn RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const Trans3D & trans, float scale);

// check Bounding Box
// should that be stored in PolyHedra of Pallet

template<typename TypeLogicalData> RayHitReturn RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const TypeLogicalData & data);
template<typename TypeLogicalData> RayHitReturn RayHitObject(const RayF3 & ray, const NewPolyHedra::Pallet & pallet, const TypeLogicalData & data);

template<typename TypeLogicalData> RayHitReturn RayHitObject(const RayF3 & ray, const NewPolyHedra::BaseDisplayObject & manager, const TypeLogicalData & data);

template<typename TypeLogicalData> RayHitReturn RayHitObject(const RayF3 & ray, const NewPolyHedra::TypeObject<TypeLogicalData> & object);
template<typename TypeLogicalData> RayHitReturn RayHitObject(const RayF3 & ray, const NewPolyHedra::TypeLogicalObject<TypeLogicalData> & object);

#endif