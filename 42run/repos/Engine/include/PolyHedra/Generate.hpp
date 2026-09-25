#ifndef  POLYHEDRA_GENERATE_HPP
# define POLYHEDRA_GENERATE_HPP

class PolyHedra;
class Image;

namespace PolyHedraGenerate
{
	PolyHedra * RegularTetraHedron(float scale = 1.0f);		// [04 04]
	PolyHedra * RegularHexaHedron(float scale = 1.0f);		// [06 08]
//	PolyHedra * RegularOctaHedron(float scale = 1.0f);		// [08 06]
//	PolyHedra * RegularDodecaHedron(float scale = 1.0f);	// [12 20]
//	PolyHedra * RegularIcosaHedron(float scale = 1.0f);		// [20 12]

	/*
		SphereCube
	*/
	PolyHedra * ConeZ(int segments, float height = 1.0f, float radius = 1.0f);
	PolyHedra * SphereY(unsigned int ring, unsigned int seg, float radius = 1.0f);
	PolyHedra * TorusY(unsigned int seg0, float radius0, unsigned int seg1, float radius1);

	PolyHedra * ImageQuad(Image img, float scale = 1.0f);
	PolyHedra * ImageFramed(Image img, float img_scale = 1.0f);
};

#endif
