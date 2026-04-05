#include "Arrow2D/Main/Data.hpp"



Arrow2D::Main::Data::Data()
	: Pos()
	, Tex()
{ }
Arrow2D::Main::Data::Data(Point2D pos)
	: Pos(pos)
	, Tex()
{ }
Arrow2D::Main::Data::Data(Point2D pos, Point3D tex)
	: Pos(pos)
	, Tex(tex)
{ }
