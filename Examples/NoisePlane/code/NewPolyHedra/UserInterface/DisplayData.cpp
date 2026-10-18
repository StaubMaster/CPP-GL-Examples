#include "NewPolyHedra/UserInterface/DisplayData.hpp"
#include "NewPolyHedra/UserInterface/LogicalData.hpp"



NewPolyHedra::UserInterface::DisplayData::DisplayData(const LogicalData & data)
	: Size(data.Size)
	, Pos(data.Pos)
	, Rot(Matrix3x3::Rotation(data.Rot))
	, Scale(data.Scale)
{ }
