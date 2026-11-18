#ifndef  SCENE_OBJECT_UI_POLYHEDRA_BASIC_3D_LOGICAL_OBJECT_HPP
# define SCENE_OBJECT_UI_POLYHEDRA_BASIC_3D_LOGICAL_OBJECT_HPP

# include "UI/NestedProperty.hpp"
# include "UI/ValueType/Trans3D.hpp"
# include "UI/PolyHedra/Basic3D/DisplayObject.hpp"

# include "Special/Basic3D/Logical/Object.hpp"
/*namespace NewPolyHedra
{
template<typename LogicalData> struct TypeLogicalObject;
namespace Basic3D
{
struct LogicalData;
typedef NewPolyHedra::TypeLogicalObject<LogicalData> LogicalObject;
};
};*/

namespace UI
{
struct LogicalObject : public NestedProperty
{
	UI::DisplayObject		DisplayObject;
	UI::Trans3D			Trans;

	LogicalObject();

	NewPolyHedra::Basic3D::LogicalObject *	Object = nullptr;

	void	Syncronize() override;
	void	Change(::NewPolyHedra::Basic3D::LogicalObject * obj);
};
};

#endif