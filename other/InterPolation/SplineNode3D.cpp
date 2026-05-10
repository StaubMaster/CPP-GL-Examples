#include "SplineNode3D.hpp"



SplineNode3D::SplineNode3D() :
	Pos(),
	Dir()
{ }
SplineNode3D::SplineNode3D(VectorF3 pos, VectorF3 dir) :
	Pos(pos),
	Dir(dir)
{ }
