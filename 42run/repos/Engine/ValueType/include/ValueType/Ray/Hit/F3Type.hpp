#ifndef  RAY_HIT_F3_TYPE_HPP
# define RAY_HIT_F3_TYPE_HPP

# include "ValueType/Ray/Hit/F3.hpp"

template<typename TypeData>
struct RayHitF3Type : public RayHitF3
{
	public:
	TypeData	Data;

	public:
	~RayHitF3Type() = default;
	RayHitF3Type() = default;
	RayHitF3Type(const RayHitF3Type & other) = default;
	RayHitF3Type & operator=(const RayHitF3Type & other) = default;

	public:
	RayHitF3Type(TypeData data)
		: RayHitF3()
		, Data(data)
	{ }

	public:
	bool	Consider(const RayHitF3 & other, TypeData data)
	{
		if (RayHitF3::Consider(other))
		{
			Data = data;
			return true;
		}
		return false;
	}
};

#endif