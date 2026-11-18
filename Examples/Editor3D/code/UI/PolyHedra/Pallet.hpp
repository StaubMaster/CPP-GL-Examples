#ifndef  SCENE_OBJECT_UI_POLYHEDRA_PALLET_HPP
# define SCENE_OBJECT_UI_POLYHEDRA_PALLET_HPP

# include "UI/NestedProperty.hpp"
# include "Control/Controls/Label.hpp"
# include "UI/PolyHedra/PolyHedraEntry.hpp"

# include "NewPolyHedra/Pallet/.hpp"

namespace UI
{
struct PolyHedraPallet : public NestedProperty
{
	UI::Control_::Label		FullCount;
	UI::Control_::Label		WireCount;
	UI::PolyHedraEntry		PolyHedraObject;

	PolyHedraPallet();

	NewPolyHedra::Pallet *	Object = nullptr;

	void	Syncronize() override;
	void	Change(::NewPolyHedra::Pallet * obj);
};
};

#endif