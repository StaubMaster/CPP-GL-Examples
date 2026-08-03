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

/* Normal Force (from Gravity)
	m: Mass
	g: Gravity
	W: Weight
	Fn: Normal Force
	W = m * g
	Fn = m * g * cos(θ)
*/
/* Kinetic Friciton
	Fn: Normal Force
	µk: Kinetic Friciton Coefficient
	Fk: Kinetic Friciton Force
	Fk = µk * Fn
*/

/* Friction (with other Force)
	m: Mass
	g: Gravity
	N: Normal Force
		goes away from Surface
	µ: Friciton Coefficient

	P: other Force
	Py: "downward" Component (parallel to the Normal)
	Px: "horizontal" Component (perpendicular to the Normal)

	not tilted:
		Px = P.X
		Py = P.Y
		N = (m * g) - Py

	tilted:
		Px = P * sin(θ)
		Py = P * cos(θ)
		N = (m * g * cos(θ)) - Py
		N = ((m * g) - P) * cos(θ)

	Ff: Friciton Force
	not sliding:
		Ff = -Px
	sliding:
		Ff = µ * N
*/

float Physics::SurfaceContext::FlatFrictionForce(float force_hori, float force_vert, float mass, float gravity) const
{
	float friction_force = -force_hori;
	float normal_force = (mass * gravity) + force_vert;
	float friction_force_limit = FrictionCoefficient * normal_force;
	if (friction_force <= friction_force_limit)
	{
		return friction_force;
	}
	else
	{
		return friction_force_limit;
	}
}

VectorF3 Physics::SurfaceContext::FlatFrictionForce(VectorF3 force, float mass, float gravity) const
{
	VectorF3 force_hori(force.X, 0.0f, force.Z);
	VectorF3 force_vert(0.0f, force.Y, 0.0f);
	float friction_force = FlatFrictionForce(force_hori.length(), force_vert.length(), mass, gravity);
	return force_hori.normalize() * friction_force; // ?
}

/*VectorF3 Physics::SurfaceContext::FrictionCounterForce(VectorF3 force, float normal_force) const
{
	float    force_len;
	VectorF3 force_dir = force.normalize(force_len);
	if (force_len < normal_force)
	{
		return force;
	}
	else
	{
		return force_dir * normal_force;
	}
}*/
