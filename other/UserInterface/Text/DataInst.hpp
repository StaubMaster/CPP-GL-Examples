#ifndef  UI_TEXT_DATA_INST_HPP
# define UI_TEXT_DATA_INST_HPP

# include "ValueType/_Include.hpp"

namespace UI
{

namespace Text
{

struct DataInst
{
	VectorF2		TextPos;
	unsigned int	CharIdx;
	unsigned int	TextIdx;
	~DataInst() = default;
	DataInst() = default;
	DataInst(const DataInst & other) = default;
	DataInst & operator=(const DataInst & other) = default;
};

};

};

#endif