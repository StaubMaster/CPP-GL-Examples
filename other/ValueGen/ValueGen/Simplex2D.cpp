#include "ValueGen/Simplex2D.hpp"
#include "ValueGen/Random.hpp"

#include <cmath>

static int perm_256[256] = {
	151,160,137, 91, 90, 15,131, 13,201, 95, 96, 53,194,233,  7,225,
	140, 36,103, 30, 69,142,  8, 99, 37,240, 21, 10, 23,190,  6,148,
	247,120,234, 75,  0, 26,197, 62, 94,252,219,203,117, 35, 11, 32,
	 57,177, 33, 88,237,149, 56, 87,174, 20,125,136,171,168, 68,175,
	 74,165, 71,134,139, 48, 27,166, 77,146,158,231, 83,111,229,122,
	 60,211,133,230,220,105, 92, 41, 55, 46,245, 40,244,102,143, 54,
	 65, 25, 63,161,  1,216, 80, 73,209, 76,132,187,208, 89, 18,169,
	200,196,135,130,116,188,159, 86,164,100,109,198,173,186,  3, 64,
	 52,217,226,250,124,123,  5,202, 38,147,118,126,255, 82, 85,212,
	207,206, 59,227, 47, 16, 58, 17,182,189, 28, 42,223,183,170,213,
	119,248,152,  2, 44,154,163, 70,221,153,101,155,167, 43,172,  9,
	129, 22, 39,253, 19, 98,108,110, 79,113,224,232,178,185,112,104,
	218,246, 97,228,251, 34,242,193,238,210,144, 12,191,179,162,241,
	 81, 51,145,235,249, 14,239,107, 49,192,214, 31,181,199,106,157,
	184, 84,204,176,115,121, 50, 45,127,  4,150,254,138,236,205, 93,
	222,114, 67, 29, 24, 72,243,141,128,195, 78, 66,215, 61,156,180,
};

static int perm_512[512];

void Simplex2D::init()
{
	for(int i = 0; i < 256; i++)
	{
		perm_512[i] = perm_256[i + 256];
	}
}

static int fastfloor(float val)
{
	return (val > 0) ? ((int)val - 0) : ((int)val - 1);
}

static VectorF2 grad2[12] = {
	VectorF2(+1,+1), VectorF2(-1,+1), VectorF2(+1,-1), VectorF2(-1,-1),
	VectorF2(+1, 0), VectorF2(-1, 0), VectorF2(+1, 0), VectorF2(-1, 0),
	VectorF2( 0,+1), VectorF2( 0,-1), VectorF2( 0,+1), VectorF2( 0,-1),
};

/*static VectorF3 grad3[12][3] = {
	VectorF3(+1,+1, 0), VectorF3(-1,+1, 0), VectorF3(+1,-1, 0), VectorF3(-1,-1, 0),
	VectorF3(+1, 0,+1), VectorF3(-1, 0,+1), VectorF3(+1, 0,-1), VectorF3(-1, 0,-1),
	VectorF3( 0,+1,+1), VectorF3( 0,-1,+1), VectorF3( 0,+1,-1), VectorF3( 0,-1,-1),
};*/

#include "ValueType/Vector/I2.hpp"

// F = (sqrt(n + 1) - 1) / n
// G = (1 - 1 / sqrt(n + 1)) / n
const float F2 = (sqrt(2.0f + 1.0f) - 1.0f) / 2.0f;
const float G2 = (1.0f - 1.0f / sqrt(2.0f + 1.0f)) / 2.0f;

//#define DEBUG

#ifdef DEBUG
# include <iostream>
# include "ValueType/_Show.hpp"
#endif

float Simplex2D::Generate(const VectorF2 & pos) const
{
	float F_sum = (pos.X + pos.Y) * F2;
#ifdef DEBUG
	std::cout << "F_sum: " << (pos.X + pos.Y) << ' ' << F_sum << '\n';
#endif

	VectorF2 posF;
	posF.X = pos.X + F_sum;
	posF.Y = pos.Y + F_sum;
#ifdef DEBUG
	std::cout << "posF: " << posF << '\n';
#endif

	VectorI2 ij0;
	ij0.X = fastfloor(posF.X);
	ij0.Y = fastfloor(posF.Y);
#ifdef DEBUG
	std::cout << "ij0: " << ij0 << '\n';
#endif

	float G_sum = (ij0.X + ij0.Y) * G2;
#ifdef DEBUG
	std::cout << "G_sum: " << (ij0.X + ij0.Y) << ' ' << G_sum << '\n';
#endif

	VectorF2 P0;
	P0.X = ij0.X - G_sum;
	P0.Y = ij0.Y - G_sum;
#ifdef DEBUG
	std::cout << "P0: " << P0 << '\n';
#endif

	VectorF2 p0;
	p0.X = pos.X - P0.X;
	p0.Y = pos.Y - P0.Y;
#ifdef DEBUG
	std::cout << "p0" << p0 << '\n';
#endif

	VectorI2 ij1;
	if (p0.X > p0.Y)
	{
		ij1.X = 1;
		ij1.Y = 0;
	}
	else
	{
		ij1.X = 0;
		ij1.Y = 1;
	}
#ifdef DEBUG
	std::cout << "ij1" << ij1 << '\n';
#endif

	VectorF2 p1;
	p1.X = p0.X - ij1.X + G2;
	p1.Y = p0.Y - ij1.Y + G2;
#ifdef DEBUG
	std::cout << "p1" << p1 << '\n';
#endif

	VectorF2 p2;
	p2.X = p0.X - 1.0f + 2.0f * G2;
	p2.Y = p0.Y - 1.0f + 2.0f * G2;
#ifdef DEBUG
	std::cout << "p2" << p2 << '\n';
#endif

	VectorI2 ij2;
	ij2.X = ij0.X & 255;
	ij2.Y = ij0.Y & 255;

	int grad_idx[3];
	grad_idx[0] = perm_512[ij2.X + 0 +     perm_512[ij2.Y + 0    ]] % 12; // (0 0)
	grad_idx[1] = perm_512[ij2.X + ij1.X + perm_512[ij2.Y + ij1.Y]] % 12; // (1 0) or (0 1)
	grad_idx[2] = perm_512[ij2.X + 1 +     perm_512[ij2.Y + 1    ]] % 12; // (1 1)

	float t[3];
	t[0] = 0.5f - p0.length2();
	t[1] = 0.5f - p1.length2();
	t[2] = 0.5f - p2.length2();

	float n[3];
	n[0] = 0.0f;
	n[1] = 0.0f;
	n[2] = 0.0f;

	if (!(t[0] < 0.0f)) { n[0] = t[0] * t[0] * t[0] * t[0] * grad2[grad_idx[0]].dot(p0); }
	if (!(t[1] < 0.0f)) { n[1] = t[1] * t[1] * t[1] * t[1] * grad2[grad_idx[1]].dot(p1); }
	if (!(t[2] < 0.0f)) { n[2] = t[2] * t[2] * t[2] * t[2] * grad2[grad_idx[2]].dot(p2); }

	return 70.0f * (n[0] + n[1] + n[2]);
}

float Simplex2D::GenerateMy(const VectorF2 & pos) const
{
	float F_sum = (pos.X + pos.Y) * F2;

	VectorF2 skew_pos = pos + F_sum;

	VectorI2 skew_idx = skew_pos.roundF().ToI();
	//skew_idx.X = fastfloor(skew.X);
	//skew_idx.Y = fastfloor(skew.Y);

	VectorF2 skew_rel = skew_pos - skew_idx.ToF();



	float G_sum = (skew_idx.X + skew_idx.Y) * G2;

	VectorF2 cube_origin = skew_idx.ToF() - G_sum;

	VectorF2 cube_offset = pos - cube_origin;



	VectorI2 indexes[3];
	indexes[0] = VectorI2(0, 0);
	if (skew_rel.X > skew_rel.Y)	{ indexes[1] = VectorI2(1, 0); }
	else							{ indexes[1] = VectorI2(0, 1); }
	indexes[2] = VectorI2(1, 1);

	float index_G[3];
	index_G[0] = (indexes[0].X + indexes[0].Y) * G2; // sum is 0
	index_G[1] = (indexes[1].X + indexes[1].Y) * G2; // sum is 1
	index_G[2] = (indexes[2].X + indexes[2].Y) * G2; // sum is 2

	VectorF2 corners[3];
	corners[0] = cube_offset - indexes[0].ToF() + index_G[0];
	corners[1] = cube_offset - indexes[1].ToF() + index_G[1];
	corners[2] = cube_offset - indexes[2].ToF() + index_G[2];

	VectorI2 idx_mod;
	idx_mod.X = skew_idx.X & 255;
	idx_mod.Y = skew_idx.Y & 255;

	int grad_idx[3];
	grad_idx[0] = perm_512[idx_mod.X + indexes[0].X + perm_512[idx_mod.Y + indexes[0].Y]] % 12;
	grad_idx[1] = perm_512[idx_mod.X + indexes[1].X + perm_512[idx_mod.Y + indexes[1].Y]] % 12;
	grad_idx[2] = perm_512[idx_mod.X + indexes[2].X + perm_512[idx_mod.Y + indexes[2].Y]] % 12;



	const float r = 0.5f;

	float dist[3];
	dist[0] = r - corners[0].length2();
	dist[1] = r - corners[1].length2();
	dist[2] = r - corners[2].length2();

	float n[3];
	n[0] = 0.0f;
	n[1] = 0.0f;
	n[2] = 0.0f;

	if (!(dist[0] < 0.0f)) { n[0] = dist[0] * dist[0] * dist[0] * dist[0] * VectorF2::dot(corners[0], grad2[grad_idx[0]]); }
	if (!(dist[1] < 0.0f)) { n[1] = dist[1] * dist[1] * dist[1] * dist[1] * VectorF2::dot(corners[1], grad2[grad_idx[1]]); }
	if (!(dist[2] < 0.0f)) { n[2] = dist[2] * dist[2] * dist[2] * dist[2] * VectorF2::dot(corners[2], grad2[grad_idx[2]]); }

	return 70.0f * (n[0] + n[1] + n[2]);
}
