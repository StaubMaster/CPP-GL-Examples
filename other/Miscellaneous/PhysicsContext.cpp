#include "PhysicsContext.hpp"
#include <math.h>



VectorF3 Physics::GravityContext::Vector() const
{
	return Direction * Acceleration;
}



float Physics::FluidContext::DragLimit(float mass, float area, float accel) const
{
	return sqrt((2 * mass * accel) / (Density * area * DragCoefficient));
}

// are these how much drag is produced, or how much remains ?
float Physics::FluidContext::Drag(float vel, float mass, float area) const
{
	float force = 0.5f * Density * vel * vel * area * DragCoefficient;
	return force / mass;
}
VectorF3 Physics::FluidContext::Drag(VectorF3 vel, float mass, float area) const
{
	float vel_len;
	vel = vel.normalize(vel_len);
	return vel * Drag(vel_len, mass, area);
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

// static Friction / kinetic Friction
float Physics::SurfaceContext::FrictionStaticForce(float mass, float accel) const
{
	float normal = mass * accel; // Weight(Force)
	return FrictionCoefficient * normal; // Force ?
}

VectorF3 Physics::SurfaceContext::FrictionCounterForce(VectorF3 force, float friction_force) const
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
