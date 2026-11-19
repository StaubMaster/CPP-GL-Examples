#include "Special/Basic3D/Display/Data.hpp"
#include "Special/Basic3D/Logical/Data.hpp"



NewPolyHedra::Basic3D::DisplayData::DisplayData(const LogicalData & data)
	: Trans(Matrix4x4::TransformForward(data.Trans))
	, Color()
{ }
