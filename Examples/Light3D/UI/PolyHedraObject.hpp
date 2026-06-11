#ifndef  UI_POLYHEDRA_OBJECT_HPP
# define UI_POLYHEDRA_OBJECT_HPP

# include "ControlsInclude.hpp"
# include "PropertyControl/Trans3D.hpp"

struct PolyHedraObject;

namespace UI
{
struct PolyHedraObject : public UI::Control::Form
{
	UI::Control::GroupBox	Pallet;
	UI::Control::Label		PalletName;
	UI::Control::Label		PalletFile;
	UI::Control::Label		PalletSkinsCount;

	UI::Control::Trans3D		Trans;

	~PolyHedraObject();
	PolyHedraObject();

	::PolyHedraObject * Object;
	void	Change(::PolyHedraObject * obj);
};
};

#endif