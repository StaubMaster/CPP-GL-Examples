#ifndef  UI_TEXT_DATA_MAIN_HPP
# define UI_TEXT_DATA_MAIN_HPP

# include "ValueType/_Include.hpp"

namespace UI
{

namespace Text
{

struct DataMain
{
	VectorF2	Pos;
	~DataMain() = default;
	DataMain() = default;
	DataMain(const DataMain & other) = default;
	DataMain & operator=(const DataMain & other) = default;
	DataMain(VectorF2 pos);
};

};

};

#endif