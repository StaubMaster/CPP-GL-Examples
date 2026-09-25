#ifndef  BOX_F_1_HPP
# define BOX_F_1_HPP

# include "ValueType/Box/_1.hpp"

struct BoxF1 : public Box_1<void, float, BoxF1>
{
	~BoxF1() = default;
	BoxF1(const BoxF1 & other) = default;
	BoxF1 & operator=(const BoxF1 & other) = default;

	BoxF1();
	BoxF1(float min, float max);
};

#endif