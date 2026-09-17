#include "ValueGen/Perlin3D.hpp"
#include "ValueGen/Random.hpp"
#include "ValueGen/Lerp.hpp"

#include "ValueType/Vector/I3.hpp"
#include "ValueType/Loop/U3.hpp"
#include "ValueType/EulerAngle3D.hpp"



VectorU3 Perlin3D::Clamp(const VectorF3 & pos) const
{
	VectorI3 count = Nodes.Size().ToI();
	VectorI3 idx = pos.ToI();
	while (idx.X < 0) { idx.X += count.X; }
	while (idx.Y < 0) { idx.Y += count.Y; }
	while (idx.Z < 0) { idx.Z += count.Z; }
	while (idx.X >= count.X) { idx.X -= count.X; }
	while (idx.Y >= count.Y) { idx.Y -= count.Y; }
	while (idx.Z >= count.Z) { idx.Z -= count.Z; }
	return idx.ToU();
}



Perlin3D::Perlin3D(const VectorU3 & size)
	: Nodes(size)
{ }




Perlin3D Perlin3D::Random(const VectorU3 & size)
{
	Perlin3D perlin(size);
	unsigned int c = perlin.Nodes.Length();
	for (unsigned int i = 0; i < c; i++)
	{
		EulerAngle3D a = EulerAngle3D::Degrees(
			Random::Float01In() * 360.0f,
			Random::Float01In() * 360.0f,
			Random::Float01In() * 360.0f
		);
		perlin.Nodes[i] = a.forward(VectorF3(0, 0, 1));
	}
	return perlin;
}



float Perlin3D::Generate(const VectorF3 & pos) const
{
	VectorF3 posF = pos.roundF();
	VectorI3 posI = posF.ToI();

	VectorF3 rel = pos - posI.ToF();
	VectorF3 rel0 = rel;
	VectorF3 rel1 = rel - VectorF3(1.0f);

	VectorU3 countU = Nodes.Size();
	VectorI3 countI = countU.ToI();

	VectorU3 idx0 = (((posI % countI) + countI) % countI).ToU();
	VectorU3 idx1 = ((idx0.ToI() + VectorI3(1)) % countI).ToU(); // do this with if checks ?

	idx0.X = idx0.X;
	idx0.Y = idx0.Y * countU.X;
	idx0.Z = idx0.Z * countU.X * countU.Y;

	idx1.X = idx1.X;
	idx1.Y = idx1.Y * countU.X;
	idx1.Z = idx1.Z * countU.X * countU.Y;

	VectorF3 nodes_cube[8] = {
		Nodes[idx0.X + idx0.Y + idx0.Z],
		Nodes[idx1.X + idx0.Y + idx0.Z],
		Nodes[idx0.X + idx1.Y + idx0.Z],
		Nodes[idx1.X + idx1.Y + idx0.Z],
		Nodes[idx0.X + idx0.Y + idx1.Z],
		Nodes[idx1.X + idx0.Y + idx1.Z],
		Nodes[idx0.X + idx1.Y + idx1.Z],
		Nodes[idx1.X + idx1.Y + idx1.Z],
	};

	VectorF3 rel_cube[8] = {
		VectorF3(rel0.X, rel0.Y, rel0.Z),
		VectorF3(rel1.X, rel0.Y, rel0.Z),
		VectorF3(rel0.X, rel1.Y, rel0.Z),
		VectorF3(rel1.X, rel1.Y, rel0.Z),
		VectorF3(rel0.X, rel0.Y, rel1.Z),
		VectorF3(rel1.X, rel0.Y, rel1.Z),
		VectorF3(rel0.X, rel1.Y, rel1.Z),
		VectorF3(rel1.X, rel1.Y, rel1.Z),
	};

	VectorF3 val_[8] = {
		nodes_cube[0b000] * rel_cube[0b000],
		nodes_cube[0b001] * rel_cube[0b001],
		nodes_cube[0b010] * rel_cube[0b010],
		nodes_cube[0b011] * rel_cube[0b011],
		nodes_cube[0b100] * rel_cube[0b100],
		nodes_cube[0b101] * rel_cube[0b101],
		nodes_cube[0b110] * rel_cube[0b110],
		nodes_cube[0b111] * rel_cube[0b111],
	};

	VectorF3 valZ[4] = {
		Lerp::interpolate(val_[0b000], val_[0b100], rel.Z),
		Lerp::interpolate(val_[0b001], val_[0b101], rel.Z),
		Lerp::interpolate(val_[0b010], val_[0b110], rel.Z),
		Lerp::interpolate(val_[0b011], val_[0b111], rel.Z),
	};

	VectorF3 valY[2] = {
		Lerp::interpolate(valZ[0b00], valZ[0b10], rel.Y),
		Lerp::interpolate(valZ[0b01], valZ[0b11], rel.Y),
	};

	VectorF3 valX = Lerp::interpolate(valY[0b0], valY[0b1], rel.X);

	return valX.X + valX.Y + valX.Z;

	/*float val_[8] = {
		VectorF3::dot(nodes_cube[0b000], rel_cube[0b000]),
		VectorF3::dot(nodes_cube[0b001], rel_cube[0b001]),
		VectorF3::dot(nodes_cube[0b010], rel_cube[0b010]),
		VectorF3::dot(nodes_cube[0b011], rel_cube[0b011]),
		VectorF3::dot(nodes_cube[0b100], rel_cube[0b100]),
		VectorF3::dot(nodes_cube[0b101], rel_cube[0b101]),
		VectorF3::dot(nodes_cube[0b110], rel_cube[0b110]),
		VectorF3::dot(nodes_cube[0b111], rel_cube[0b111]),
	};*/

	/*float valZ[4] = {
		interpolate(val_[0b000], val_[0b100], rel.Z),
		interpolate(val_[0b001], val_[0b101], rel.Z),
		interpolate(val_[0b010], val_[0b110], rel.Z),
		interpolate(val_[0b011], val_[0b111], rel.Z),
	};*/

	/*float valY[2] = {
		interpolate(valZ[0b00], valZ[0b10], rel.Y),
		interpolate(valZ[0b01], valZ[0b11], rel.Y),
	};*/

	//float valX = interpolate(valY[0b0], valY[0b1], rel.X);

	//return valX;

	/*return interpolate(
		interpolate(
			interpolate(
				VectorF3::dot(Nodes[i0.X + i0.Y + i0.Z], VectorF3(rel0.X, rel0.Y, rel0.Z)),
				VectorF3::dot(Nodes[i0.X + i0.Y + i1.Z], VectorF3(rel0.X, rel0.Y, rel1.Z)),
				rel.Z),
			interpolate(
				VectorF3::dot(Nodes[i0.X + i1.Y + i0.Z], VectorF3(rel0.X, rel1.Y, rel0.Z)),
				VectorF3::dot(Nodes[i0.X + i1.Y + i1.Z], VectorF3(rel0.X, rel1.Y, rel1.Z)),
				rel.Z),
			rel.Y),
		interpolate(
			interpolate(
				VectorF3::dot(Nodes[i1.X + i0.Y + i0.Z], VectorF3(rel1.X, rel0.Y, rel0.Z)),
				VectorF3::dot(Nodes[i1.X + i0.Y + i1.Z], VectorF3(rel1.X, rel0.Y, rel1.Z)),
				rel.Z),
			interpolate(
				VectorF3::dot(Nodes[i1.X + i1.Y + i0.Z], VectorF3(rel1.X, rel1.Y, rel0.Z)),
				VectorF3::dot(Nodes[i1.X + i1.Y + i1.Z], VectorF3(rel1.X, rel1.Y, rel1.Z)),
				rel.Z),
			rel.Y),
		rel.X);*/
}
