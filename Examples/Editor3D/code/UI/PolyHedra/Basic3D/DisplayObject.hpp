#ifndef  SCENE_OBJECT_UI_POLYHEDRA_BASIC_3D_DISPLAY_OBJECT_HPP
# define SCENE_OBJECT_UI_POLYHEDRA_BASIC_3D_DISPLAY_OBJECT_HPP

# include "UI/NestedProperty.hpp"
# include "Control/Controls/Label.hpp"
# include "UI/PolyHedra/Pallet.hpp"

# include "Special/Basic3D/Display/Object.hpp"
/*namespace NewPolyHedra
{
template<typename LogicalData, typename DisplayData> struct TypeDisplayObject;
namespace Basic3D
{
struct LogicalData;
struct DisplayData;
typedef NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData> DisplayObject;
};
};*/

namespace UI
{
struct DisplayObject : public NestedProperty
{
	UI::Control_::Label		FullCount;
	UI::Control_::Label		WireCount;
	UI::PolyHedraPallet		PalletObject;

	DisplayObject();

	NewPolyHedra::Basic3D::DisplayObject *	Object = nullptr;

	void	Syncronize() override;
	void	Change(::NewPolyHedra::Basic3D::DisplayObject * obj);
};
};

#endif