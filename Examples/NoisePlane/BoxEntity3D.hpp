#ifndef  BOX_ENTITY_3D_HPP
# define BOX_ENTITY_3D_HPP

# include "ValueType/Vector/F3.hpp"
# include "ValueType/Box/F3.hpp"

# include "Generics/Container/Array.hpp"

# include "Axis/Enums.hpp"

struct BoxEntity3D_CollisionTime
{
	float		Time = 0.0f / 0.0f;
	VectorF3	Normal;
	//AxisRel		Axis; // instread of Normal ?

	~BoxEntity3D_CollisionTime() = default;
	BoxEntity3D_CollisionTime() = default;
	BoxEntity3D_CollisionTime(const BoxEntity3D_CollisionTime & other) = default;
	BoxEntity3D_CollisionTime & operator=(const BoxEntity3D_CollisionTime & other) = default;

	BoxEntity3D_CollisionTime(VectorF3 t, VectorF3 dir);
	void	Consider(const BoxEntity3D_CollisionTime & other);
};

struct BoxEntity3D_CollisionSide // could be compressed into a Byte
{
	bool	None = true; // all others are false
	bool	PrevX = false;
	bool	PrevY = false;
	bool	PrevZ = false;
	bool	NextX = false;
	bool	NextY = false;
	bool	NextZ = false;
	//bool	Here; // currently inside of something ?

	~BoxEntity3D_CollisionSide() = default;
	BoxEntity3D_CollisionSide() = default;
	BoxEntity3D_CollisionSide(const BoxEntity3D_CollisionSide & other) = default;
	BoxEntity3D_CollisionSide & operator=(const BoxEntity3D_CollisionSide & other) = default;

	void	Consider(const AxisRel & axis);
	void	Consider(const VectorF3 & vec);
	void	Consider(const BoxEntity3D_CollisionSide & other);
};

struct BoxEntity3D
{
	BoxF3			Box;
	VectorF3		Pos;
	VectorF3		Vel;

	~BoxEntity3D() = default;
	BoxEntity3D() = default;
	BoxEntity3D(const BoxEntity3D & other) = default;
	BoxEntity3D & operator=(const BoxEntity3D & other) = default;

	BoxEntity3D_CollisionTime	FindCollisionTime(const BoxF3 & other) const;
	BoxEntity3D_CollisionTime	FindCollisionTime(const Container::Array<BoxF3> & boxes) const;

	BoxEntity3D_CollisionSide	Collide(const Container::Array<BoxF3> & boxes, float time_limit);
};

#endif