#ifndef  BOX_I_3_HPP
# define BOX_I_3_HPP

# include "ValueType/Vector/I3.hpp"
# include "ValueType/Box/_3.hpp"

struct BoxI3 : public Box_3<int, VectorI3, BoxI3>
{
	~BoxI3() = default;
	BoxI3(const BoxI3 & other) = default;
	BoxI3 & operator=(const BoxI3 & other) = default;

	BoxI3();
	BoxI3(VectorI3 min, VectorI3 max);
};

#endif