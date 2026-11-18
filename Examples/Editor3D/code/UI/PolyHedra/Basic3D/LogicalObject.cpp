#include "UI/PolyHedra/Basic3D/LogicalObject.hpp"
#include "Special/Basic3D/Logical/Object.hpp"



UI::LogicalObject::LogicalObject()
	: NestedProperty("LogicalObject")
	, DisplayObject()
	, Trans("Trans")
{
	AutoAnchorYType = EAutoAnchorType::StackMin;
	Make_Anchor_X_Both(nullptr, nullptr);
	Make_Anchor_Y_Both(nullptr, nullptr);

	DisplayObject.Make_Anchor_X_Both(nullptr, nullptr);
	Trans.Make_Anchor_X_Both(nullptr, nullptr);

	ChildInsert(DisplayObject);
	ChildInsert(Trans);

	Change(nullptr);

	Minimize();
}



void UI::LogicalObject::Syncronize()
{
	DisplayObject.Syncronize();
	Trans.Syncronize();
}

#include "Special/Basic3D/Display/Object.hpp"
void UI::LogicalObject::Change(::NewPolyHedra::Basic3D::LogicalObject * obj)
{
	if (obj != nullptr)
	{ Object = obj; }
	else
	{ Object = nullptr; }

	if (Object != nullptr)
	{
		Show();
		DisplayObject.Change(dynamic_cast<NewPolyHedra::Basic3D::DisplayObject*>(Object -> DisplayObject));
		Trans.Change(&(Object -> Data.Trans));
	}
	else
	{
		Hide();
		DisplayObject.Change(nullptr);
		Trans.Change(nullptr);
	}
}
