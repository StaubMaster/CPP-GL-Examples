#ifndef  BOX_U_3_HPP
# define BOX_U_3_HPP

# include "ValueType/Vector/U3.hpp"
# include "ValueType/Box/_3.hpp"

struct BoxU3 : public Box_3<unsigned int, VectorU3, BoxU3>
{
	~BoxU3() = default;
	BoxU3(const BoxU3 & other) = default;
	BoxU3 & operator=(const BoxU3 & other) = default;

	BoxU3();
	BoxU3(VectorU3 min, VectorU3 max);
};

#endif