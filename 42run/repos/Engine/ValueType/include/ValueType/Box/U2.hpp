#ifndef  BOX_U_2_HPP
# define BOX_U_2_HPP

# include "ValueType/Vector/U2.hpp"
# include "ValueType/Box/_2.hpp"

struct BoxU2 : public Box_2<unsigned int, VectorU2, BoxU2>
{
	~BoxU2() = default;
	BoxU2(const BoxU2 & other) = default;
	BoxU2 & operator=(const BoxU2 & other) = default;

	BoxU2();
	BoxU2(VectorU2 min, VectorU2 max);
};

#endif