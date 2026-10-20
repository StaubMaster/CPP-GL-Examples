#include "DisplayHelp/Normalized.hpp"

#include "ValueType/Box/F3.hpp"
#include "BoxEntity3D.hpp"

#include "NewPolyHedra/DataType/TransScaleColor3D/Object.hpp"
#include "NewPolyHedra/DataType/TransScaleColor3D/Logical/Data.hpp"
#include "ValueType/Color/F4.hpp"

PolyHedra *				DisplayHelp::Box_PolyHedra = nullptr;
NewPolyHedra::Pallet *	DisplayHelp::Box_Pallet = nullptr;

void DisplayHelp::Normalized(NewPolyHedra::Pallet & pallet, const BoxF3 & box)
{
	TransScaleColor3D::Object obj(&pallet);
	obj.Data().Trans.Position = box.Center();
	obj.Data().Scale = box.Size() * 0.5f;
	obj.Data().Color = ColorF4(1, 1, 1);
	obj.HideFull(); obj.ShowWire();
}
void DisplayHelp::Normalized(NewPolyHedra::Pallet & pallet, const BoxEntity3D & box_entity)
{
	VectorF3 pos = box_entity.Pos;
	VectorF3 size = box_entity.Box.Size() * 0.5f;
	VectorF3 center = box_entity.Box.Center();

	{
		{
			TransScaleColor3D::Object obj(&pallet);
			obj.Data().Trans.Position = pos + VectorF3(center.X, 0, 0);
			obj.Data().Scale = VectorF3(size.X, 0, 0);
			obj.Data().Color = ColorF4(1, 0, 0);
			obj.HideFull(); obj.ShowWire();
		}
		{
			TransScaleColor3D::Object obj(&pallet);
			obj.Data().Trans.Position = pos + VectorF3(0, center.Y, 0);
			obj.Data().Scale = VectorF3(0, size.Y, 0);
			obj.Data().Color = ColorF4(0, 1, 0);
			obj.HideFull(); obj.ShowWire();
		}
		{
			TransScaleColor3D::Object obj(&pallet);
			obj.Data().Trans.Position = pos + VectorF3(0, 0, center.Z);
			obj.Data().Scale = VectorF3(0, 0, size.Z);
			obj.Data().Color = ColorF4(0, 0, 1);
			obj.HideFull(); obj.ShowWire();
		}
	}

	Normalized(pallet, box_entity.Box + box_entity.Pos);
}
void DisplayHelp::Normalized(NewPolyHedra::Pallet & pallet, const Container::Array<BoxF3> & boxes)
{
	for (unsigned int i = 0; i < boxes.Length(); i++)
	{
		Normalized(pallet, boxes[i]);
	}
}

void DisplayHelp::Normalized(const BoxF3 & box)
{
	Normalized(*Box_Pallet, box);
}
void DisplayHelp::Normalized(const Container::Array<BoxF3> & boxes)
{
	Normalized(*Box_Pallet, boxes);
}
void DisplayHelp::Normalized(const BoxEntity3D & box)
{
	Normalized(*Box_Pallet, box);
}
