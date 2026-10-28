#include "UI/Change3D/Base.hpp"



bool Change3D::Base::IndicatorsIsVisible() const
{
	return IsVisible;
}
void Change3D::Base::IndicatorsShow()
{
	IsVisible = true;
}
void Change3D::Base::IndicatorsHide()
{
	IsVisible = false;
}



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
