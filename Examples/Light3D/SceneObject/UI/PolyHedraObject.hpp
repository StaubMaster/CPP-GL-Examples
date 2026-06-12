#ifndef  SCENE_OBJECT_CONTROL_POLYHEDRA_OBJECT_HPP
# define SCENE_OBJECT_CONTROL_POLYHEDRA_OBJECT_HPP

# include "Control/GroupBox.hpp"
# include "Control/Label.hpp"
# include "PropertyControl/Trans3D.hpp"

struct PolyHedraObject;
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

	UI::Control::Trans3D	Trans;

	~PolyHedraObject();
	PolyHedraObject();

	::PolyHedraObject * Object;
	void	Change(::SceneObject_PolyHedraObject * obj);
	void	Update();
};
};
};

#endif