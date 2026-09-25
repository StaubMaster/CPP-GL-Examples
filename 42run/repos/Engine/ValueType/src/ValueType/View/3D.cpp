#include "ValueType/View/3D.hpp"



View3D::~View3D() { }

View3D::View3D()
	: Trans()
	, Depth(
		DepthFactors(0.1f, 1000.0f),
		RangeF(0.8f, 1.0f),
		ColorF4(0.5f, 0.5f, 0.5f)
	)
	, FOV(Angle::Degrees(90))
{ }



View3D View3D::Default()
{
	View3D view;
	return view;
}



void View3D::ChangeRelative(const Trans3D & trans)
{
	Trans.Position += Trans.Rotation.forward(trans.Position);
	Trans.Rotation = Trans.Rotation.reverse(trans.Rotation);
}
void View3D::ChangeAbsoluteFlatY(const Trans3D & trans)
{
	EulerAngle3D e(Angle(), Angle(), Trans.Rotation.Y2);
	Trans.Position += e.forward(trans.Position);
	Trans.Rotation += trans.Rotation;
	Trans.Rotation.X1.clampPI();
}



//VectorF3 View3D::forward(VectorF3 p) const { }
//VectorF3 View3D::reverse(VectorF3 p) const { }
