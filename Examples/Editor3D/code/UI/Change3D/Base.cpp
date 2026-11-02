#include "UI/Change3D/Base.hpp"



bool Change3D::Base::IsNone() const
{
	return (
		HoveringIsNone() &&
		SelectedIsNone()
	);
}
void Change3D::Base::MakeNone()
{
	HoveringMakeNone();
	SelectedMakeNone();
}
