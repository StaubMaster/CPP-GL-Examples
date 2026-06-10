#ifndef  UI_POLYHEDRA_OBJECT_HPP
# define UI_POLYHEDRA_OBJECT_HPP

# include "ControlsInclude.hpp"
# include "ObjectControl/VectorF3.hpp"
# include "ObjectControl/EulerAngle3D.hpp"

struct PolyHedraObject;

namespace UI
{
struct PolyHedraObject : public UI::Control::Form
{
	UI::Control::GroupBox	Pallet;
	UI::Control::Label		PalletName;
	UI::Control::Label		PalletFile;
	UI::Control::Label		PalletSkinsCount;

	UI::Control::GroupBox		Trans;
	UI::Control::VectorF3		TransPos;
	UI::Control::EulerAngle3D	TransRot;

	~PolyHedraObject();
	PolyHedraObject();

	::PolyHedraObject * Object;
	void	Change(::PolyHedraObject * obj);
};
};

#endif