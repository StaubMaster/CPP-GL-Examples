#ifndef  UI_CONTROL_DATA_HPP
# define UI_CONTROL_DATA_HPP

#include "ValueType/_Include.hpp"



namespace UI
{

namespace Control
{

struct Main_Data
{
	VectorF2	Pos;

	Main_Data();
	Main_Data(VectorF2 pos);
};
struct Inst_Data
{
	VectorF2	Min;
	VectorF2	Max;
	float	Layer;
	ColorF4	Col;

	Inst_Data();
	Inst_Data(VectorF2 min, VectorF2 max, float layer, ColorF4 col);
};

};

};

#endif