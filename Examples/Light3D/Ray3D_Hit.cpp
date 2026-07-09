#include "Ray3D_Hit.hpp"



#include "ValueType/Trans/3D.hpp"

#include "PolyHedra/Data.hpp"

#include "NewPolyHedra/DataType/Basic3D/ObjectData.hpp"
#include "NewPolyHedra/DataType/TransScaleColor3D/ObjectData.hpp"

#include "NewPolyHedra/Type/Object.hpp"
#include "NewPolyHedra/Type/PalletObjectData.hpp"

#include "NewPolyHedra/PalletObjectManager.hpp"
#include "NewPolyHedra/Pallet.hpp"

#include "ValueType/TriangleF3.hpp"
#include "ValueType/InteractF3.hpp"



RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const Trans3D & trans)
{
	RayHitF3Type<unsigned int> hit_return;
	for (unsigned int i = 0; i < polyhedra.Faces.Count(); i++)
	{
		const PolyHedra::Face & face = polyhedra.Faces[i];

		TriangleF3 triangle(
			polyhedra.Corners[face.udx[0]].Position,
			polyhedra.Corners[face.udx[1]].Position,
			polyhedra.Corners[face.udx[2]].Position
		);

		triangle.A = trans.forward(triangle.A);
		triangle.B = trans.forward(triangle.B);
		triangle.C = trans.forward(triangle.C);

		RayHitF3 hit = InteractF3::Triangle(ray, triangle);
		hit_return.Consider(hit, i);
	}
	return hit_return;
}
RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const Trans3D & trans, float scale)
{
	RayHitF3Type<unsigned int> hit_return;
	for (unsigned int i = 0; i < polyhedra.Faces.Count(); i++)
	{
		const PolyHedra::Face & face = polyhedra.Faces[i];

		TriangleF3 triangle(
			polyhedra.Corners[face.udx[0]].Position,
			polyhedra.Corners[face.udx[1]].Position,
			polyhedra.Corners[face.udx[2]].Position
		);

		triangle.A = trans.forward(triangle.A * scale);
		triangle.B = trans.forward(triangle.B * scale);
		triangle.C = trans.forward(triangle.C * scale);

		RayHitF3 hit = InteractF3::Triangle(ray, triangle);
		hit_return.Consider(hit, i);
	}
	return hit_return;
}

template<> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const Basic3D::ObjectData & data)
{
	return RayHitObject(ray, polyhedra, data.Trans);
}
template<> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const TransScaleColor3D::ObjectData & data)
{
	return RayHitObject(ray, polyhedra, data.Trans, data.Scale);
}

template<typename TypeData> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Pallet & pallet, const TypeData & data)
{
	const PolyHedra * polyhedra = pallet.Object;
	if (polyhedra == nullptr) { return RayHitF3Type<unsigned int>(); }
	return RayHitObject(ray, *polyhedra, data);
}
template<typename TypeData> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::PalletObjectManager & manager, const TypeData & data)
{
	const NewPolyHedra::Pallet * pallet = manager.Pallet;
	if (pallet == nullptr) { return RayHitF3Type<unsigned int>(); }
	return RayHitObject(ray, *pallet, data);
}
template<typename TypeData> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Type_Object<TypeData> & object)
{
	const NewPolyHedra::PalletObjectManager * manager = object.Manager();
	if (manager == nullptr) { return RayHitF3Type<unsigned int>(); }
	return RayHitObject(ray, *manager, object.Data());
}
template<typename TypeData> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Type_PalletObjectData<TypeData> & object)
{
	const NewPolyHedra::PalletObjectManager * manager = object.Manager;
	if (manager == nullptr) { return RayHitF3Type<unsigned int>(); }
	return RayHitObject(ray, *manager, object.Data);
}

template RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Pallet & pallet, const Basic3D::ObjectData & data);
template RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::PalletObjectManager & manager, const Basic3D::ObjectData & data);
template RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Type_Object<Basic3D::ObjectData> & object);
template RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Type_PalletObjectData<Basic3D::ObjectData> & object);

template RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Pallet & pallet, const TransScaleColor3D::ObjectData & data);
template RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::PalletObjectManager & manager, const TransScaleColor3D::ObjectData & data);
template RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Type_Object<TransScaleColor3D::ObjectData> & object);
template RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Type_PalletObjectData<TransScaleColor3D::ObjectData> & object);
