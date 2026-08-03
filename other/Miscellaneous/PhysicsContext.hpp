#ifndef  PHYSICS_CONTEXT_HPP
# define PHYSICS_CONTEXT_HPP

# include "ValueType/Vector/F3.hpp"

typedef float Mass;		// kg

typedef float Length;	// m
typedef float Area;		// m*m
typedef float Volume;	// m*m*m
typedef float Density;	// kg/m*m*m

typedef float Time;		// s
typedef float Speed;	// m/s
typedef float Accel;	// m/s*s
typedef float Force;	// kg*m/s*s

namespace Physics
{
	struct GravityContext
	{
		VectorF3	Direction = VectorF3(0.0f, -1.0f, 0.0f);
		float		Acceleration = 1.0f;

		VectorF3	Vector() const; // Force
	};

	struct FluidContext
	{
		float		Density = 0.001f; // Air
		float		DragCoefficient = 1.0f;

		// DragVelLimit
		float		DragLimit(float mass, float area, float accel) const;

		// DragForec
		float		Drag(float vel, float mass, float area) const;		// DragVel
		VectorF3	Drag(VectorF3 vel, float mass, float area) const;	// DragVel
	};

	struct SurfaceContext
	{
		float		FrictionCoefficient = 0.5f;

		float		FlatFrictionForce(float force_hori, float force_vert, float mass, float gravity) const;
		VectorF3	FlatFrictionForce(VectorF3 force, float mass, float gravity) const;
	};
};

#endif