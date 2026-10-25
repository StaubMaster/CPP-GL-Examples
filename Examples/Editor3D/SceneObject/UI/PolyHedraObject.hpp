#ifndef  SCENE_OBJECT_CONTROL_POLYHEDRA_OBJECT_HPP
# define SCENE_OBJECT_CONTROL_POLYHEDRA_OBJECT_HPP

# include "Control/Controls/GroupBox.hpp"
# include "Control/Controls/Label.hpp"
# include "ValueTypeUI/Trans3D.hpp"

# include "Special/Basic3D/Logical/Object.hpp"

struct SceneObject_PolyHedraObject;

namespace UI
{
namespace Control
{
struct PolyHedraObject : public GroupBox
{
	UI::Control::GroupBox	Pallet;
	UI::Control::Label		PalletName;
	UI::Control::Label		PalletFile;
	UI::Control::Label		PalletSkinsCount;
	UI::Control::Button		PalletChange;

	UI::Control::Trans3D	Trans;

	~PolyHedraObject();
	PolyHedraObject();

	NewPolyHedra::Basic3D::LogicalObject *	Object;

	void	Change(::SceneObject_PolyHedraObject * obj);
	void	Syncronize();
};
};
};

#endif