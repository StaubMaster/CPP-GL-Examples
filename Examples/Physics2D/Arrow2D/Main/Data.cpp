#include "Arrow2D/Main/Data.hpp"



Arrow2D::Main::Data::Data()
	: Pos()
	, Tex()
{ }
Arrow2D::Main::Data::Data(VectorF2 pos)
	: Pos(pos)
	, Tex()
{ }
Arrow2D::Main::Data::Data(VectorF2 pos, VectorF3 tex)
	: Pos(pos)
	, Tex(tex)
{ }
