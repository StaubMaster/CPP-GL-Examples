#ifndef  PHYSICS_2D_INST_DATA_HPP
# define PHYSICS_2D_INST_DATA_HPP

# include "ValueType/Trans2D.hpp"

namespace Physics2D
{
namespace Inst
{
struct Data
{
	Trans2D		Now;
	Trans2D		Vel;
	Data();
	Data(Trans2D now);
	Data(Trans2D now, Trans2D vel);
};
};
};

#endif