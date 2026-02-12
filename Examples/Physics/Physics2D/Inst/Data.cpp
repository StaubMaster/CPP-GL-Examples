#include "Data.hpp"



Physics2D::Inst::Data::Data()
	: Pos()
	, Vel()
{ }
Physics2D::Inst::Data::Data(Point2D pos)
	: Pos(pos)
	, Vel()
{ }
Physics2D::Inst::Data::Data(Point2D pos, Point2D vel)
	: Pos(pos)
	, Vel(vel)
{ }