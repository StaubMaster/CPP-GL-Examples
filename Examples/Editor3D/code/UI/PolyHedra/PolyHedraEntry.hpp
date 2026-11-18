#ifndef  SCENE_OBJECT_UI_POLYHEDRA_ENTRY_HPP
# define SCENE_OBJECT_UI_POLYHEDRA_ENTRY_HPP

# include "UI/NestedProperty.hpp"
# include "Control/Controls/Label.hpp"

class PolyHedra;
struct PolyHedraEntry;
class PolyHedraManager;

namespace UI
{
struct PolyHedraEntry : public NestedProperty
{
	static ::PolyHedraManager *	Manager;

	UI::Control_::Label		File;
	// PolyHedra

	PolyHedraEntry();

	::PolyHedraEntry *	Object = nullptr;

	void	Syncronize() override;
	void	Change(::PolyHedra * obj);
};
};

#endif