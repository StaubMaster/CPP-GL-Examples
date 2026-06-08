#include "PhysicsContext.hpp"
#include <math.h>



VectorF3 PhysicsContext::CalcGravityVec() const
{
	return GravityDirection * GravityAcl;
}

float PhysicsContext::CalcDragLimit(float mass, float area, float accel) const
{
	return sqrt((2 * mass * accel) / (DragFluidDensity * area * DragCoefficient));
}
float PhysicsContext::CalcTerminalVel(float mass, float area) const
{
	return CalcDragLimit(mass, area, GravityAcl);
}

float PhysicsContext::CalcDrag(float vel, float mass, float area) const
{
	float force = 0.5f * DragFluidDensity * vel * vel * area * DragCoefficient;
	return force / mass;
}
VectorF3 PhysicsContext::CalcDragVec(VectorF3 vel, float mass, float area) const
{
	float vel_len;
	vel = vel.normalize(vel_len);
	return vel * CalcDrag(vel_len, mass, area);
}

/*
	uk: Kinetic Friciton Coefficient
	Fk: Kinetic Friciton
	Fn: Normal Force

	Fk = uk * Fn

	N: Normal Force
	mg: Weight (Mass * Gravity)

	P: External Force
	Py: "downward Component of External Force" (parallel to Normal Force ?)
	Px: horisontal Component of External Force (perpendicular to Normal Force ?)

	N = mg + Py

	Ff: Friciton Force
	Ff = -Px (not sliding)
	Ff = u * N (sliding)
*/

// static Friction
float PhysicsContext::CalcFriction(float mass) const
{
	float normal = mass * GravityAcl;
	return FrictionCoefficient * normal;
}
VectorF3 PhysicsContext::CalcFriction(VectorF3 force, float friction_force) const
{
	float    force_length;
	VectorF3 force_normal = force.normalize(force_length);
	if (friction_force > force_length)
	{
		return force;
	}
	else
	{
		return force_normal * friction_force;
	}
}

VectorF3 PhysicsContext::CalculateVel(VectorF3 vel, float mass, float area) const
{
	return CalcGravityVec() - CalcDragVec(vel, mass, area);
}
