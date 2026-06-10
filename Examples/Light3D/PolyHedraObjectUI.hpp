#ifndef  POLYHEDRA_OBJECT_UI_HPP
# define POLYHEDRA_OBJECT_UI_HPP

# include "ControlsInclude.hpp"

struct PolyHedraObject;

struct PolyHedraObjectUI : public UI::Control::Form
{
	UI::Control::GroupBox	Pallet;
	UI::Control::Label		PalletName;
	UI::Control::Label		PalletFile;
	UI::Control::Label		PalletSkinsCount;

	UI::Control::GroupBox	Trans;
	UI::Control::GroupBox	TransPos;
	UI::Control::Label		TransPosX;
	UI::Control::Label		TransPosZ;
	UI::Control::Label		TransPosY;
	UI::Control::GroupBox	TransRot;
	UI::Control::Label		TransRotX;
	UI::Control::Label		TransRotZ;
	UI::Control::Label		TransRotY;

	PolyHedraObject * Object;

	~PolyHedraObjectUI();
	PolyHedraObjectUI();

	void	Change(PolyHedraObject * obj);
};

#endif