#include "Inst/Physics2D/Data.hpp"



Physics2D::Inst::Data::Data()
	: Now()
	, Vel()
{ }
Physics2D::Inst::Data::Data(Trans2D now)
	: Now(now)
	, Vel()
{ }
Physics2D::Inst::Data::Data(Trans2D now, Trans2D vel)
	: Now(now)
	, Vel(vel)
{ }