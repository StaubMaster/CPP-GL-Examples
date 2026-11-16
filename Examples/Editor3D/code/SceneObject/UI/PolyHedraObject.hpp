#ifndef  SCENE_OBJECT_CONTROL_POLYHEDRA_OBJECT_HPP
# define SCENE_OBJECT_CONTROL_POLYHEDRA_OBJECT_HPP

# include "Control/Controls/GroupBox.hpp"
# include "Control/Controls/Label.hpp"
# include "ValueTypeUI/Trans3D.hpp"

//# include "Special/Basic3D/Logical/Object.hpp"
namespace NewPolyHedra
{
template<typename LogicalData> struct TypeLogicalObject;
namespace Basic3D
{
struct LogicalData;
typedef NewPolyHedra::TypeLogicalObject<LogicalData> LogicalObject;
};
};

struct SceneObject_PolyHedraObject;

namespace UI
{
namespace Control_
{
struct PolyHedraObject : public GroupBox
{
	UI::Control_::GroupBox	Pallet;
	UI::Control_::Label		PalletName;
	UI::Control_::Label		PalletFile;
	UI::Control_::Label		PalletSkinsCount;
	UI::Control_::Button	PalletChange;

	UI::Control_::Trans3D	Trans;

	~PolyHedraObject();
	PolyHedraObject();

	NewPolyHedra::Basic3D::LogicalObject *	Object;

	void	Change(::SceneObject_PolyHedraObject * obj);
	void	Syncronize();
};
};
};

#endif