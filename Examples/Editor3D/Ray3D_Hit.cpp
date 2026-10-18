#include "Ray3D_Hit.hpp"



#include "ValueType/Trans/3D.hpp"

#include "PolyHedra/Data.hpp"

#include "NewPolyHedra/DataType/Basic3D/Logical/Object.hpp"
#include "NewPolyHedra/DataType/TransScaleColor3D/Logical/Object.hpp"

#include "NewPolyHedra/Type/Object.hpp"
#include "NewPolyHedra/Type/Display/Object.hpp"

#include "NewPolyHedra/Pallet/Manager.hpp"
#include "NewPolyHedra/Pallet/.hpp"

#include "ValueType/TriangleF3.hpp"
#include "ValueType/Interact/3D.hpp"



RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const Trans3D & trans)
{
	RayHitF3Type<unsigned int> hit_return;
	for (unsigned int i = 0; i < polyhedra.Faces.Count(); i++)
	{
		const PolyHedra::Face & face = polyhedra.Faces[i];
		if (!face.Check(polyhedra.Corners.Count())) { continue; }

		TriangleF3 triangle(
			polyhedra.Corners[face.idx[0]].Position,
			polyhedra.Corners[face.idx[1]].Position,
			polyhedra.Corners[face.idx[2]].Position
		);

		triangle.A = trans.forward(triangle.A);
		triangle.B = trans.forward(triangle.B);
		triangle.C = trans.forward(triangle.C);

		hit_return.Consider(Interact3D::Triangle(ray, triangle), i);
	}
	return hit_return;
}
RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const Trans3D & trans, float scale)
{
	RayHitF3Type<unsigned int> hit_return;
	for (unsigned int i = 0; i < polyhedra.Faces.Count(); i++)
	{
		const PolyHedra::Face & face = polyhedra.Faces[i];
		if (!face.Check(polyhedra.Corners.Count())) { continue; }

		TriangleF3 triangle(
			polyhedra.Corners[face.idx[0]].Position,
			polyhedra.Corners[face.idx[1]].Position,
			polyhedra.Corners[face.idx[2]].Position
		);

		triangle.A = trans.forward(triangle.A * scale);
		triangle.B = trans.forward(triangle.B * scale);
		triangle.C = trans.forward(triangle.C * scale);

		hit_return.Consider(Interact3D::Triangle(ray, triangle), i);
	}
	return hit_return;
}

template<> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const NewPolyHedra::Basic3D::LogicalData & data)
{
	return RayHitObject(ray, polyhedra, data.Trans);
}
template<> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const TransScaleColor3D::LogicalData & data)
{
	return RayHitObject(ray, polyhedra, data.Trans, data.Scale.X);
}

template<typename TypeLogicalData> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Pallet & pallet, const TypeLogicalData & data)
{
	const PolyHedra * polyhedra = pallet.Object;
	if (polyhedra == nullptr) { return RayHitF3Type<unsigned int>(); }
	return RayHitObject(ray, *polyhedra, data);
}
template<typename TypeLogicalData> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::BaseDisplayObject & manager, const TypeLogicalData & data)
{
	const NewPolyHedra::Pallet & pallet = manager.PalletObject;
	return RayHitObject(ray, pallet, data);
}
template<typename TypeData> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Type_Object<TypeData> & object)
{
	const NewPolyHedra::BaseDisplayObject * manager = object.Manager();
	if (manager == nullptr) { return RayHitF3Type<unsigned int>(); }
	return RayHitObject(ray, *manager, object.Data());
}
template<typename TypeData> RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::TypeLogicalObject<TypeData> & object)
{
	const NewPolyHedra::BaseDisplayObject * manager = object.Graphics;
	if (manager == nullptr) { return RayHitF3Type<unsigned int>(); }
	return RayHitObject(ray, *manager, object.Data);
}

template RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Pallet & pallet, const NewPolyHedra::Basic3D::LogicalData & data);
template RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::BaseDisplayObject & manager, const NewPolyHedra::Basic3D::LogicalData & data);
template RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Type_Object<NewPolyHedra::Basic3D::LogicalData> & object);
template RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::TypeLogicalObject<NewPolyHedra::Basic3D::LogicalData> & object);

template RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Pallet & pallet, const TransScaleColor3D::LogicalData & data);
template RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::BaseDisplayObject & manager, const TransScaleColor3D::LogicalData & data);
template RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::Type_Object<TransScaleColor3D::LogicalData> & object);
template RayHitF3Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra::TypeLogicalObject<TransScaleColor3D::LogicalData> & object);
