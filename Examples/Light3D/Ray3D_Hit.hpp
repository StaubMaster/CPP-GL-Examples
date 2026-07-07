#ifndef  RAY_3D_HIT_HPP
# define RAY_3D_HIT_HPP

# include "Miscellaneous/Container/Array.hpp"

# include "ValueType/Ray/F3.hpp"
# include "ValueType/Ray/Hit/F3Type.hpp"



struct Trans3D;
class PolyHedra;

struct NewPolyHedra_Pallet;
struct NewPolyHedra_PalletObjectManager;

namespace Basic3D { struct ObjectData; };
namespace TransScaleColor3D { struct ObjectData; };
template<typename TypeData> struct NewPolyHedra_Type_Object;
template<typename TypeData> struct NewPolyHedra_Type_PalletObjectData;

RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const Trans3D & trans);
RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const Trans3D & trans, float scale);

RayHitF3Type<unsigned int> RayHitObject0(const RayF3 & ray, const NewPolyHedra_Type_Object<Basic3D::ObjectData> & object);
RayHitF3Type<unsigned int> RayHitObject1(const RayF3 & ray, const NewPolyHedra_Type_Object<TransScaleColor3D::ObjectData> & object);

RayHitF3Type<unsigned int> RayHitObject0(const RayF3 & ray, const NewPolyHedra_Type_PalletObjectData<Basic3D::ObjectData> & object);
RayHitF3Type<unsigned int> RayHitObject1(const RayF3 & ray, const NewPolyHedra_Type_PalletObjectData<TransScaleColor3D::ObjectData> & object);

#endif