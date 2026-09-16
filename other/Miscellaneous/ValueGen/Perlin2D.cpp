#include "ValueGen/Perlin2D.hpp"
#include "ValueGen/Random.hpp"
#include "ValueGen/Lerp.hpp"

#include "ValueType/Vector/I2.hpp"
#include "ValueType/Loop/U2.hpp"
#include "ValueType/Angle.hpp"



VectorU2 Perlin2D::Clamp(const VectorF2 & pos) const
{
	VectorI2 size = Nodes.Size().ToI();
	VectorI2 idx = pos.ToI();
	while (idx.X < 0) { idx.X += size.X; }
	while (idx.Y < 0) { idx.Y += size.Y; }
	while (idx.X >= size.X) { idx.X -= size.X; }
	while (idx.Y >= size.Y) { idx.Y -= size.Y; }
	return idx.ToU();
}



Perlin2D::Perlin2D(const VectorU2 & size)
	: Nodes(size)
{ }

Perlin2D Perlin2D::Random(const VectorU2 & size)
{
	Perlin2D perlin(size);
	unsigned int c = perlin.Nodes.Length();
	for (unsigned int i = 0; i < c; i++)
	{
		Angle a = Angle::Degrees(Random::Float01In() * 360.0f);
		perlin.Nodes[i] = a.forward(VectorF2(0, 1));
	}
	return perlin;
}



float Perlin2D::Generate(const VectorF2 & pos) const
{
	VectorF2 posF = pos.roundF();
	VectorI2 posI = posF.ToI();

	VectorF2 rel = pos - posI.ToF();
	VectorF2 rel0 = rel;
	VectorF2 rel1 = rel - VectorF2(1.0f);

	VectorU2 count = Nodes.Size();
	VectorU2 i0 = (((posI % count.ToI()) + count.ToI()) % count.ToI()).ToU();
	VectorU2 i1 = (i0 + 1u) % count;

	i0.Y = i0.Y * count.X;
	i1.Y = i1.Y * count.X;

	float dotY[4] = {
		VectorF2::dot(Nodes[i0.X + i0.Y], VectorF2(rel0.X, rel0.Y)),
		VectorF2::dot(Nodes[i1.X + i0.Y], VectorF2(rel1.X, rel0.Y)),
		VectorF2::dot(Nodes[i0.X + i1.Y], VectorF2(rel0.X, rel1.Y)),
		VectorF2::dot(Nodes[i1.X + i1.Y], VectorF2(rel1.X, rel1.Y)),
	};

	float dotX[2] = {
		Lerp::interpolate(dotY[0b00], dotY[0b10], rel.Y),
		Lerp::interpolate(dotY[0b01], dotY[0b11], rel.Y),
	};

	return Lerp::interpolate(dotX[0b0], dotX[0b1], rel.X);

	/*return interpolate(
		interpolate(
			VectorF2::dot(Nodes[i0.X + i0.Y], VectorF2(rel0.X, rel0.Y)),
			VectorF2::dot(Nodes[i0.X + i1.Y], VectorF2(rel0.X, rel1.Y)),
			rel.Y),
		interpolate(
			VectorF2::dot(Nodes[i1.X + i0.Y], VectorF2(rel1.X, rel0.Y)),
			VectorF2::dot(Nodes[i1.X + i1.Y], VectorF2(rel1.X, rel1.Y)),
			rel.Y),
		rel.X);*/
}
