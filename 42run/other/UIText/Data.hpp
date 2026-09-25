#ifndef  UI_TEXT_DATA
# define UI_TEXT_DATA

# include "ValueType/_Include.hpp"

namespace UI
{

namespace Text
{

struct Main_Data
{
	VectorF2	Pos;

	Main_Data();
	Main_Data(VectorF2 pos);
};

struct Inst_Data
{
	VectorF2		TextPos;
	unsigned int	CharIdx;
	unsigned int	TextIdx;

	Inst_Data();
};

};

};

#endif