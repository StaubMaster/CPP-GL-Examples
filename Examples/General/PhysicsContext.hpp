#ifndef  PHYSICS_CONTEXT_HPP
# define PHYSICS_CONTEXT_HPP

# include "ValueType/Vector/F3.hpp"

struct PhysicsContext
{
	VectorF3	GravityDirection = VectorF3(0.0f, -1.0f, 0.0f);
	float		GravityAcl = 1.0f;

	VectorF3	CalcGravityVec() const;



	float	DragFluidDensity = 0.001f;
	float	DragCoefficient = 1.0f;

	float	CalcDragLimit(float mass, float area, float accel) const;
	float	CalcTerminalVel(float mass, float area) const;

	float		CalcDrag(float vel, float mass, float area) const;
	VectorF3	CalcDragVec(VectorF3 vel, float mass, float area) const;

	// static Friction
	float	FrictionCoefficient = 0.5f; // kinetic Friction
	float		CalcFriction(float mass) const;
	VectorF3	CalcFriction(VectorF3 force, float friction_force) const;

	VectorF3	CalculateVel(VectorF3 vel, float mass, float area) const;
};

#endif