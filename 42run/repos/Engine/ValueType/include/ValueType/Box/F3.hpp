#ifndef  BOX_F_3_HPP
# define BOX_F_3_HPP

# include "ValueType/Vector/F3.hpp"
# include "ValueType/Box/_3.hpp"

struct BoxF3 : public Box_3<float, VectorF3, BoxF3>
{
	~BoxF3() = default;
	BoxF3(const BoxF3 & other) = default;
	BoxF3 & operator=(const BoxF3 & other) = default;

	BoxF3();
	BoxF3(VectorF3 min, VectorF3 max);

	// put into Box_3 ?
	// this uses float for time. so keep here ?
	static VectorF3		CollisionTimePerAxis(
		const BoxF3 & box0, const VectorF3 & vel0,
		const BoxF3 & box1
	);
	static VectorF3		CollisionTimePerAxisNaN(
		const BoxF3 & box0, const VectorF3 & vel0,
		const BoxF3 & box1
	);
};

#endif