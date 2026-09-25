#include "PolyHedra/Generate.hpp"
#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Data.hpp"

#include "PolyHedra/Skin/Skin.hpp"
#include "PolyHedra/Skin/Data.hpp"

#include "Graphics/Texture/Generate.hpp"

#include "ValueType/Angle.hpp"
#include "ValueType/EulerAngle3D.hpp"
#include "ValueType/Vector/F2.hpp"

#include "Image.hpp"

//#include "FileInfo.hpp"
//#include "DirectoryInfo.hpp"
//#include "DataShow.hpp"

#include "Debug.hpp"
#include <sstream>
#include <iostream>





PolyHedra * PolyHedraGenerate::RegularTetraHedron(float scale)
{
	PolyHedra * polyhedra = new PolyHedra();
	//polyhedra -> Name = "TetraHedron";
	polyhedra -> File = "::TetraHedron::"; // put () with parameters ?

	polyhedra -> Insert_Corn(-scale, -scale, -scale);
	polyhedra -> Insert_Corn(+scale, +scale, -scale);
	polyhedra -> Insert_Corn(+scale, -scale, +scale);
	polyhedra -> Insert_Corn(-scale, +scale, +scale);

	polyhedra -> Insert_Face3(0b00, 0b01, 0b10);
	polyhedra -> Insert_Face3(0b00, 0b10, 0b11);
	polyhedra -> Insert_Face3(0b00, 0b11, 0b01);
	polyhedra -> Insert_Face3(0b11, 0b10, 0b01);



	::Skin * skin = new ::Skin();
	skin -> Size = VectorU2(8, 4);
	skin -> Images.Insert(Texture::Generate::Orientation3D());

	unsigned int idx;

	idx = skin -> Corners.Count();
	skin -> Corners.Insert(Skin::Corner(0.00f, 0.00f, 0));
	skin -> Corners.Insert(Skin::Corner(0.00f, 0.50f, 0));
	skin -> Corners.Insert(Skin::Corner(0.25f, 0.00f, 0));
	skin -> Insert_Face3(idx + 0, idx + 1, idx + 2);

	idx = skin -> Corners.Count();
	skin -> Corners.Insert(Skin::Corner(0.25f, 0.00f, 0));
	skin -> Corners.Insert(Skin::Corner(0.00f, 0.50f, 0));
	skin -> Corners.Insert(Skin::Corner(0.50f, 0.00f, 0));
	skin -> Insert_Face3(idx + 0, idx + 1, idx + 2);

	idx = skin -> Corners.Count();
	skin -> Corners.Insert(Skin::Corner(0.50f, 0.00f, 0));
	skin -> Corners.Insert(Skin::Corner(0.00f, 0.50f, 0));
	skin -> Corners.Insert(Skin::Corner(0.75f, 0.00f, 0));
	skin -> Insert_Face3(idx + 0, idx + 1, idx + 2);

	idx = skin -> Corners.Count();
	skin -> Corners.Insert(Skin::Corner(0.75f, 0.00f, 0));
	skin -> Corners.Insert(Skin::Corner(0.00f, 0.50f, 0));
	skin -> Corners.Insert(Skin::Corner(1.00f, 0.00f, 0));
	skin -> Insert_Face3(idx + 0, idx + 1, idx + 2);

	//skin -> Insert_Face3(Skin::Corner(0.00f, 0.00f, 0), Skin::Corner(0.00f, 0.50f, 0), Skin::Corner(0.25f, 0.00f, 0));
	//skin -> Insert_Face3(Skin::Corner(0.25f, 0.00f, 0), Skin::Corner(0.00f, 0.50f, 0), Skin::Corner(0.50f, 0.00f, 0));
	//skin -> Insert_Face3(Skin::Corner(0.50f, 0.00f, 0), Skin::Corner(0.00f, 0.50f, 0), Skin::Corner(0.75f, 0.00f, 0));
	//skin -> Insert_Face3(Skin::Corner(0.75f, 0.00f, 0), Skin::Corner(0.00f, 0.50f, 0), Skin::Corner(1.00f, 0.00f, 0));

	skin -> Done();


	polyhedra -> Skin = skin;
	polyhedra -> Done();
	return polyhedra;
}

PolyHedra * PolyHedraGenerate::RegularHexaHedron(float scale)
{
	PolyHedra * polyhedra = new PolyHedra();
	//polyhedra -> Name = "HexaHedron";
	polyhedra -> File = "::HexaHedron::"; // put () with parameters ?

	polyhedra -> Insert_Corn(-scale, -scale, -scale);
	polyhedra -> Insert_Corn(+scale, -scale, -scale);
	polyhedra -> Insert_Corn(-scale, +scale, -scale);
	polyhedra -> Insert_Corn(+scale, +scale, -scale);
	polyhedra -> Insert_Corn(-scale, -scale, +scale);
	polyhedra -> Insert_Corn(+scale, -scale, +scale);
	polyhedra -> Insert_Corn(-scale, +scale, +scale);
	polyhedra -> Insert_Corn(+scale, +scale, +scale);

	polyhedra -> Insert_Face4(0b000, 0b010, 0b001, 0b011);
	polyhedra -> Insert_Face4(0b000, 0b100, 0b010, 0b110);
	polyhedra -> Insert_Face4(0b000, 0b001, 0b100, 0b101);

	polyhedra -> Insert_Face4(0b111, 0b110, 0b101, 0b100);
	polyhedra -> Insert_Face4(0b111, 0b101, 0b011, 0b001);
	polyhedra -> Insert_Face4(0b111, 0b011, 0b110, 0b010);




	::Skin * skin = new ::Skin();
	skin -> Size = VectorU2(8, 4);
	skin -> Images.Insert(Texture::Generate::Orientation3D());

	unsigned int idx;

	idx = skin -> Corners.Count();
	skin -> Corners.Insert(Skin::Corner(0.00f, 0.00f, 0));
	skin -> Corners.Insert(Skin::Corner(0.00f, 0.50f, 0));
	skin -> Corners.Insert(Skin::Corner(0.25f, 0.00f, 0));
	skin -> Corners.Insert(Skin::Corner(0.25f, 0.50f, 0));
	skin -> Insert_Face4(idx + 0, idx + 1, idx + 2, idx + 3);
	idx = skin -> Corners.Count();
	skin -> Corners.Insert(Skin::Corner(0.25f, 0.00f, 0));
	skin -> Corners.Insert(Skin::Corner(0.25f, 0.50f, 0));
	skin -> Corners.Insert(Skin::Corner(0.50f, 0.00f, 0));
	skin -> Corners.Insert(Skin::Corner(0.50f, 0.50f, 0));
	skin -> Insert_Face4(idx + 0, idx + 1, idx + 2, idx + 3);
	idx = skin -> Corners.Count();
	skin -> Corners.Insert(Skin::Corner(0.50f, 0.00f, 0));
	skin -> Corners.Insert(Skin::Corner(0.50f, 0.50f, 0));
	skin -> Corners.Insert(Skin::Corner(0.75f, 0.00f, 0));
	skin -> Corners.Insert(Skin::Corner(0.75f, 0.50f, 0));
	skin -> Insert_Face4(idx + 0, idx + 1, idx + 2, idx + 3);

	idx = skin -> Corners.Count();
	skin -> Corners.Insert(Skin::Corner(0.25f, 1.00f, 0));
	skin -> Corners.Insert(Skin::Corner(0.00f, 1.00f, 0));
	skin -> Corners.Insert(Skin::Corner(0.25f, 0.50f, 0));
	skin -> Corners.Insert(Skin::Corner(0.00f, 0.50f, 0));
	skin -> Insert_Face4(idx + 0, idx + 1, idx + 2, idx + 3);
	idx = skin -> Corners.Count();
	skin -> Corners.Insert(Skin::Corner(0.50f, 1.00f, 0));
	skin -> Corners.Insert(Skin::Corner(0.25f, 1.00f, 0));
	skin -> Corners.Insert(Skin::Corner(0.50f, 0.50f, 0));
	skin -> Corners.Insert(Skin::Corner(0.25f, 0.50f, 0));
	skin -> Insert_Face4(idx + 0, idx + 1, idx + 2, idx + 3);
	idx = skin -> Corners.Count();
	skin -> Corners.Insert(Skin::Corner(0.75f, 1.00f, 0));
	skin -> Corners.Insert(Skin::Corner(0.50f, 1.00f, 0));
	skin -> Corners.Insert(Skin::Corner(0.75f, 0.50f, 0));
	skin -> Corners.Insert(Skin::Corner(0.50f, 0.50f, 0));
	skin -> Insert_Face4(idx + 0, idx + 1, idx + 2, idx + 3);

	/*skin -> Insert_Face4(
		Skin::Corner(0.00f, 0.00f, 0),
		Skin::Corner(0.00f, 0.50f, 0),
		Skin::Corner(0.25f, 0.00f, 0),
		Skin::Corner(0.25f, 0.50f, 0)
	);
	skin -> Insert_Face4(
		Skin::Corner(0.25f, 0.00f, 0),
		Skin::Corner(0.25f, 0.50f, 0),
		Skin::Corner(0.50f, 0.00f, 0),
		Skin::Corner(0.50f, 0.50f, 0)
	);
	skin -> Insert_Face4(
		Skin::Corner(0.50f, 0.00f, 0),
		Skin::Corner(0.50f, 0.50f, 0),
		Skin::Corner(0.75f, 0.00f, 0),
		Skin::Corner(0.75f, 0.50f, 0)
	);*/

	/*skin -> Insert_Face4(
		Skin::Corner(0.25f, 1.00f, 0),
		Skin::Corner(0.00f, 1.00f, 0),
		Skin::Corner(0.25f, 0.50f, 0),
		Skin::Corner(0.00f, 0.50f, 0)
	);
	skin -> Insert_Face4(
		Skin::Corner(0.50f, 1.00f, 0),
		Skin::Corner(0.25f, 1.00f, 0),
		Skin::Corner(0.50f, 0.50f, 0),
		Skin::Corner(0.25f, 0.50f, 0)
	);
	skin -> Insert_Face4(
		Skin::Corner(0.75f, 1.00f, 0),
		Skin::Corner(0.50f, 1.00f, 0),
		Skin::Corner(0.75f, 0.50f, 0),
		Skin::Corner(0.50f, 0.50f, 0)
	);*/

	skin -> Done();

	polyhedra -> Skin = skin;
	polyhedra -> Done();

	return polyhedra;
}



PolyHedra * PolyHedraGenerate::ConeZ(int segments, float height, float radius)
{
	PolyHedra * polyhedra = new PolyHedra();
	//polyhedra -> Name = "ConeZ";
	polyhedra -> File = "::ConeZ::"; // put () with parameters ?

	::Skin * skin = new ::Skin();
	skin -> Size = VectorU2(8, 4);
	skin -> Images.Insert(Texture::Generate::Orientation3D());

	EulerAngle3D angle;

	int idx_frst = polyhedra -> Corners.Count();
	polyhedra -> Insert_Corn(0, 0, +height);
	for (int i = 0; i < segments; i++)
	{
		angle.Z0 = Angle::Section(segments) * i;
		polyhedra -> Insert_Corn(angle.reverse(VectorF3(0, +radius, -height)));
	}
	int idx_last = polyhedra -> Corners.Count();
	polyhedra -> Insert_Corn(0, 0, -height);

	for (int i = 0; i < segments; i++)
	{
		float tex0 = (0.0f + i) / segments;
		float tex1 = (1.0f + i) / segments;
		float texM = (0.5f + i) / segments;

		int idx_curr = ((i + 0) % segments) + 1;
		int idx_next = ((i + 1) % segments) + 1;

		polyhedra -> Insert_Face4(
			idx_frst,
			idx_next,
			idx_curr,
			idx_last
		);

		unsigned int idx = skin -> Corners.Count();
		skin -> Corners.Insert(Skin::Corner(texM, 0.0f, 0));
		skin -> Corners.Insert(Skin::Corner(tex1, 1.0f, 0));
		skin -> Corners.Insert(Skin::Corner(tex0, 1.0f, 0));
		skin -> Corners.Insert(Skin::Corner(texM, 0.0f, 0));
		skin -> Insert_Face4(
			idx + 0,
			idx + 1,
			idx + 2,
			idx + 3
		);
	}

	skin -> Done();
	polyhedra -> Skin = skin;
	polyhedra -> Done();
	return polyhedra;
}

PolyHedra * PolyHedraGenerate::SphereY(unsigned int ring, unsigned int seg, float radius)
{
	PolyHedra * polyhedra = new PolyHedra();
	//polyhedra -> Name = "SpherePolarY";
	polyhedra -> File = "::SpherePolarY::";

	unsigned int pole_idx;
	unsigned int ring_0_idx;
	unsigned int ring_1_idx;

	unsigned int face_count = 0;

	pole_idx = 0;
	polyhedra -> Insert_Corn(0, -radius, 0);
	ring_0_idx = 1;
	for (unsigned int s = 0; s < seg; s++)
	{
		polyhedra -> Insert_Face3(pole_idx
			, ((s + 1) % seg) + ring_0_idx
			, ((s + 0) % seg) + ring_0_idx
		);
		face_count++;
	}

	EulerAngle3D	angle;

	float vert;
	float hori;
	for (unsigned int r = 0; r < ring; r++)
	{
		vert = (1.0f + r) / (1.0f + ring);
		vert = 0.5f - vert;
		angle.X1 = Angle::Radians(vert * Angle::Half);

		ring_1_idx = 1 + (r * seg);
		ring_0_idx = ring_1_idx - seg;
		for (unsigned int s = 0; s < seg; s++)
		{
			hori = ((1.0 * s) + (0.5f * r)) / seg;
			angle.Y2 = Angle::Radians(hori * Angle::Full);

			polyhedra -> Insert_Corn(angle.forward(VectorF3(0, 0, radius)));

			if (r != 0)
			{
				unsigned int s0 = (s + 0) % seg;
				unsigned int s1 = (s + 1) % seg;

				polyhedra -> Insert_Face3(ring_0_idx + s0, ring_0_idx + s1, ring_1_idx + s0);
				face_count++;

				polyhedra -> Insert_Face3(ring_0_idx + s1, ring_1_idx + s1, ring_1_idx + s0);
				face_count++;
			}
		}
	}

	ring_1_idx = 1 + (ring * seg);
	polyhedra -> Insert_Corn(0, +radius, 0);
	pole_idx = ring_1_idx - seg;
	for (unsigned int s = 0; s < seg; s++)
	{
		polyhedra -> Insert_Face3(ring_1_idx
			, ((s + 0) % seg) + pole_idx
			, ((s + 1) % seg) + pole_idx
		);
	}

	polyhedra -> Done();
	return polyhedra;
}

PolyHedra * PolyHedraGenerate::TorusY(unsigned int seg0, float radius0, unsigned int seg1, float radius1)
{
	PolyHedra * polyhedra = new PolyHedra();
	//polyhedra -> Name = "TorusY";
	polyhedra -> File = "::TorusY::";

	EulerAngle3D angle0;
	EulerAngle3D angle1;

	VectorF3 pos;
	for (unsigned int s0 = 0; s0 < seg0; s0++)
	{
		for (unsigned int s1 = 0; s1 < seg1; s1++)
		{
			angle0.Z0 = Angle::Section(seg0) * s0;
			angle1.Y2 = Angle::Section(seg1) * s1;

			pos = angle0.forward(VectorF3(radius0, 0, 0));
			pos = angle1.forward(VectorF3(radius1, 0, 0) + pos);

			polyhedra -> Insert_Corn(pos);

			unsigned int s00 = ((s0 + 0) % seg0) * seg1;
			unsigned int s01 = ((s0 + 1) % seg0) * seg1;
			unsigned int s10 = ((s1 + 0) % seg1);
			unsigned int s11 = ((s1 + 1) % seg1);

			polyhedra -> Insert_Face4(
				s00 + s10,
				s00 + s11,
				s01 + s10,
				s01 + s11
			);
		}
	}

	polyhedra -> Done();
	return polyhedra;
}



PolyHedra * PolyHedraGenerate::ImageQuad(Image img, float scale)
{
	PolyHedra * polyhedra = new PolyHedra();
	//polyhedra -> Name = "DuoHedra";
	polyhedra -> File = "::DuoHedra::"; // put () with parameters ?

	polyhedra -> Insert_Corn(-scale, -scale, 0);
	polyhedra -> Insert_Corn(-scale, +scale, 0);
	polyhedra -> Insert_Corn(+scale, -scale, 0);
	polyhedra -> Insert_Corn(+scale, +scale, 0);

	polyhedra -> Insert_Face4(0, 1, 2, 3);



	::Skin * skin = new ::Skin();
	skin -> Size = img.Size();
	skin -> Images.Insert(img);

	unsigned int idx = skin -> Corners.Count();
	skin -> Corners.Insert(Skin::Corner(0.0f, 1.0f, 0));
	skin -> Corners.Insert(Skin::Corner(0.0f, 0.0f, 0));
	skin -> Corners.Insert(Skin::Corner(1.0f, 1.0f, 0));
	skin -> Corners.Insert(Skin::Corner(1.0f, 0.0f, 0));
	skin -> Insert_Face4(
		idx + 0,
		idx + 1,
		idx + 2,
		idx + 3
	);

	skin -> Done();

	polyhedra -> Skin = skin;
	polyhedra -> Done();
	return polyhedra;
}

PolyHedra * PolyHedraGenerate::ImageFramed(Image img, float img_scale)
{
	Debug::Log << "Polyhedra: Generate: FramedImage: (" << img.W() << "x" << img.H() << ") ..." << Debug::Done;

	PolyHedra * polyhedra = new PolyHedra();
	//polyhedra -> Name = "FramedImage";
	polyhedra -> File = "::FramedImage::"; // put () with parameters ?

	::Skin * skin = new ::Skin();
	skin -> Size = img.Size();
	skin -> Images.Insert(img);
	skin -> Images.Insert(Texture::Generate::Wood16x16());
	/*{
		FileInfo file(R"(F:\Code\GitRepositorys\C++\CPP-GL-Examples\other\Engine\media\Images\Test.png)");
		skin -> Images.Insert(file.LoadImage());
	}*/

	VectorF3 FrameSizeInn(0, 0, 0.05f);
	VectorF3 FrameSizeOut(0.5f, 0.5f, 0.1f);

	VectorF2 tex01[4];
	tex01[0] = VectorF2(0.0f, 1.0f);
	tex01[1] = VectorF2(0.0f, 0.0f);
	tex01[2] = VectorF2(1.0f, 1.0f);
	tex01[3] = VectorF2(1.0f, 0.0f);

	VectorF2 scale(img.W() * img_scale * 0.01f * 0.5f, img.H() * img_scale * 0.01f * 0.5f);

	polyhedra -> Insert_Corn(-scale.X, -scale.Y, -FrameSizeInn.Z);
	polyhedra -> Insert_Corn(+scale.X, -scale.Y, -FrameSizeInn.Z);
	polyhedra -> Insert_Corn(+scale.X, +scale.Y, -FrameSizeInn.Z);
	polyhedra -> Insert_Corn(-scale.X, +scale.Y, -FrameSizeInn.Z);
	polyhedra -> Insert_Face4(0, 3, 1, 2);

	unsigned int idx = skin -> Corners.Count();
	skin -> Corners.Insert(Skin::Corner(tex01[0], 0));
	skin -> Corners.Insert(Skin::Corner(tex01[1], 0));
	skin -> Corners.Insert(Skin::Corner(tex01[2], 0));
	skin -> Corners.Insert(Skin::Corner(tex01[3], 0));

	skin -> Insert_Face4(
		idx + 0,
		idx + 1,
		idx + 2,
		idx + 3
	);

	tex01[0] = VectorF2(1.0f, 0.0f);
	tex01[1] = VectorF2(0.0f, 0.0f);
	tex01[2] = VectorF2(1.0f, 1.0f);
	tex01[3] = VectorF2(0.0f, 1.0f);

	unsigned int off0 = 0;
	unsigned int off1 = 0;



	float Frame_Mid_X = scale.X / FrameSizeOut.X;

	VectorF2 texScaleMiddleInnX = VectorF2(Frame_Mid_X * 2, FrameSizeInn.Z / (FrameSizeOut.Z * 2));
	Skin::Corner texMiddleInnX_vec[4];
	texMiddleInnX_vec[0] = Skin::Corner((tex01[0] * texScaleMiddleInnX) - VectorF2(Frame_Mid_X, 0.0f), 1);
	texMiddleInnX_vec[1] = Skin::Corner((tex01[1] * texScaleMiddleInnX) - VectorF2(Frame_Mid_X, 0.0f), 1);
	texMiddleInnX_vec[2] = Skin::Corner((tex01[2] * texScaleMiddleInnX) - VectorF2(Frame_Mid_X, 0.0f), 1);
	texMiddleInnX_vec[3] = Skin::Corner((tex01[3] * texScaleMiddleInnX) - VectorF2(Frame_Mid_X, 0.0f), 1);

	VectorF2 texScaleMiddleOutX = VectorF2(Frame_Mid_X * 2, 1.0f);
	Skin::Corner texMiddleOutX_vec[4];
	texMiddleOutX_vec[0] = Skin::Corner((tex01[0] * texScaleMiddleOutX) - VectorF2(Frame_Mid_X, 0.0f), 1);
	texMiddleOutX_vec[1] = Skin::Corner((tex01[1] * texScaleMiddleOutX) - VectorF2(Frame_Mid_X, 0.0f), 1);
	texMiddleOutX_vec[2] = Skin::Corner((tex01[2] * texScaleMiddleOutX) - VectorF2(Frame_Mid_X, 0.0f), 1);
	texMiddleOutX_vec[3] = Skin::Corner((tex01[3] * texScaleMiddleOutX) - VectorF2(Frame_Mid_X, 0.0f), 1);

	VectorF2 texScaleCornerMinX = VectorF2(1.0f, 1.0f);
	Skin::Corner texCornerMinX_vec[4];
	texCornerMinX_vec[0] = Skin::Corner((tex01[0] * texScaleCornerMinX) + VectorF2(Frame_Mid_X, 0.0f), 1);
	texCornerMinX_vec[1] = Skin::Corner((tex01[1] * texScaleCornerMinX) + VectorF2(Frame_Mid_X, 0.0f), 1);
	texCornerMinX_vec[2] = Skin::Corner((tex01[2] * texScaleCornerMinX) + VectorF2(Frame_Mid_X, 0.0f), 1);
	texCornerMinX_vec[3] = Skin::Corner((tex01[3] * texScaleCornerMinX) + VectorF2(Frame_Mid_X, 0.0f), 1);

	VectorF2 texScaleCornerMaxX = VectorF2(1.0f, 1.0f);
	Skin::Corner texCornerMaxX_vec[4];
	texCornerMaxX_vec[0] = Skin::Corner((tex01[0] * texScaleCornerMaxX) - VectorF2(Frame_Mid_X, 0.0f), 1);
	texCornerMaxX_vec[1] = Skin::Corner((tex01[1] * texScaleCornerMaxX) - VectorF2(Frame_Mid_X, 0.0f), 1);
	texCornerMaxX_vec[2] = Skin::Corner((tex01[2] * texScaleCornerMaxX) - VectorF2(Frame_Mid_X, 0.0f), 1);
	texCornerMaxX_vec[3] = Skin::Corner((tex01[3] * texScaleCornerMaxX) - VectorF2(Frame_Mid_X, 0.0f), 1);

	unsigned int texMiddleInnX[4];
	texMiddleInnX[0] = skin -> Corners.Count(); skin -> Corners.Insert(texMiddleInnX_vec[0]);
	texMiddleInnX[1] = skin -> Corners.Count(); skin -> Corners.Insert(texMiddleInnX_vec[1]);
	texMiddleInnX[2] = skin -> Corners.Count(); skin -> Corners.Insert(texMiddleInnX_vec[2]);
	texMiddleInnX[3] = skin -> Corners.Count(); skin -> Corners.Insert(texMiddleInnX_vec[3]);

	unsigned int texMiddleOutX[4];
	texMiddleOutX[0] = skin -> Corners.Count(); skin -> Corners.Insert(texMiddleOutX_vec[0]);
	texMiddleOutX[1] = skin -> Corners.Count(); skin -> Corners.Insert(texMiddleOutX_vec[1]);
	texMiddleOutX[2] = skin -> Corners.Count(); skin -> Corners.Insert(texMiddleOutX_vec[2]);
	texMiddleOutX[3] = skin -> Corners.Count(); skin -> Corners.Insert(texMiddleOutX_vec[3]);

	unsigned int texCornerMinX[4];
	texCornerMinX[0] = skin -> Corners.Count(); skin -> Corners.Insert(texCornerMinX_vec[0]);
	texCornerMinX[1] = skin -> Corners.Count(); skin -> Corners.Insert(texCornerMinX_vec[1]);
	texCornerMinX[2] = skin -> Corners.Count(); skin -> Corners.Insert(texCornerMinX_vec[2]);
	texCornerMinX[3] = skin -> Corners.Count(); skin -> Corners.Insert(texCornerMinX_vec[3]);

	unsigned int texCornerMaxX[4];
	texCornerMaxX[0] = skin -> Corners.Count(); skin -> Corners.Insert(texCornerMaxX_vec[0]);
	texCornerMaxX[1] = skin -> Corners.Count(); skin -> Corners.Insert(texCornerMaxX_vec[1]);
	texCornerMaxX[2] = skin -> Corners.Count(); skin -> Corners.Insert(texCornerMaxX_vec[2]);
	texCornerMaxX[3] = skin -> Corners.Count(); skin -> Corners.Insert(texCornerMaxX_vec[3]);



	float Frame_Mid_Y = scale.Y / FrameSizeOut.Y;

	VectorF2 texScaleMiddleInnY = VectorF2(Frame_Mid_Y * 2, FrameSizeInn.Z / (FrameSizeOut.Z * 2));
	Skin::Corner texMiddleInnY_vec[4];
	texMiddleInnY_vec[0] = Skin::Corner((tex01[0] * texScaleMiddleInnY) - VectorF2(Frame_Mid_Y, 0.0f), 1);
	texMiddleInnY_vec[1] = Skin::Corner((tex01[1] * texScaleMiddleInnY) - VectorF2(Frame_Mid_Y, 0.0f), 1);
	texMiddleInnY_vec[2] = Skin::Corner((tex01[2] * texScaleMiddleInnY) - VectorF2(Frame_Mid_Y, 0.0f), 1);
	texMiddleInnY_vec[3] = Skin::Corner((tex01[3] * texScaleMiddleInnY) - VectorF2(Frame_Mid_Y, 0.0f), 1);

	VectorF2 texScaleMiddleOutY = VectorF2(Frame_Mid_Y * 2, 1.0f);
	Skin::Corner texMiddleOutY_vec[4];
	texMiddleOutY_vec[0] = Skin::Corner((tex01[0] * texScaleMiddleOutY) - VectorF2(Frame_Mid_Y, 0.0f), 1);
	texMiddleOutY_vec[1] = Skin::Corner((tex01[1] * texScaleMiddleOutY) - VectorF2(Frame_Mid_Y, 0.0f), 1);
	texMiddleOutY_vec[2] = Skin::Corner((tex01[2] * texScaleMiddleOutY) - VectorF2(Frame_Mid_Y, 0.0f), 1);
	texMiddleOutY_vec[3] = Skin::Corner((tex01[3] * texScaleMiddleOutY) - VectorF2(Frame_Mid_Y, 0.0f), 1);

	VectorF2 texScaleCornerMinY = VectorF2(1.0f, 1.0f);
	Skin::Corner texCornerMinY_vec[4];
	texCornerMinY_vec[0] = Skin::Corner((tex01[0] * texScaleCornerMinY) + VectorF2(Frame_Mid_Y, 0.0f), 1);
	texCornerMinY_vec[1] = Skin::Corner((tex01[1] * texScaleCornerMinY) + VectorF2(Frame_Mid_Y, 0.0f), 1);
	texCornerMinY_vec[2] = Skin::Corner((tex01[2] * texScaleCornerMinY) + VectorF2(Frame_Mid_Y, 0.0f), 1);
	texCornerMinY_vec[3] = Skin::Corner((tex01[3] * texScaleCornerMinY) + VectorF2(Frame_Mid_Y, 0.0f), 1);

	VectorF2 texScaleCornerMaxY = VectorF2(1.0f, 1.0f);
	Skin::Corner texCornerMaxY_vec[4];
	texCornerMaxY_vec[0] = Skin::Corner((tex01[0] * texScaleCornerMaxY) - VectorF2(Frame_Mid_Y, 0.0f), 1);
	texCornerMaxY_vec[1] = Skin::Corner((tex01[1] * texScaleCornerMaxY) - VectorF2(Frame_Mid_Y, 0.0f), 1);
	texCornerMaxY_vec[2] = Skin::Corner((tex01[2] * texScaleCornerMaxY) - VectorF2(Frame_Mid_Y, 0.0f), 1);
	texCornerMaxY_vec[3] = Skin::Corner((tex01[3] * texScaleCornerMaxY) - VectorF2(Frame_Mid_Y, 0.0f), 1);

	unsigned int texMiddleInnY[4];
	texMiddleInnY[0] = skin -> Corners.Count(); skin -> Corners.Insert(texMiddleInnY_vec[0]);
	texMiddleInnY[1] = skin -> Corners.Count(); skin -> Corners.Insert(texMiddleInnY_vec[1]);
	texMiddleInnY[2] = skin -> Corners.Count(); skin -> Corners.Insert(texMiddleInnY_vec[2]);
	texMiddleInnY[3] = skin -> Corners.Count(); skin -> Corners.Insert(texMiddleInnY_vec[3]);

	unsigned int texMiddleOutY[4];
	texMiddleOutY[0] = skin -> Corners.Count(); skin -> Corners.Insert(texMiddleOutY_vec[0]);
	texMiddleOutY[1] = skin -> Corners.Count(); skin -> Corners.Insert(texMiddleOutY_vec[1]);
	texMiddleOutY[2] = skin -> Corners.Count(); skin -> Corners.Insert(texMiddleOutY_vec[2]);
	texMiddleOutY[3] = skin -> Corners.Count(); skin -> Corners.Insert(texMiddleOutY_vec[3]);

	unsigned int texCornerMinY[4];
	texCornerMinY[0] = skin -> Corners.Count(); skin -> Corners.Insert(texCornerMinY_vec[0]);
	texCornerMinY[1] = skin -> Corners.Count(); skin -> Corners.Insert(texCornerMinY_vec[1]);
	texCornerMinY[2] = skin -> Corners.Count(); skin -> Corners.Insert(texCornerMinY_vec[2]);
	texCornerMinY[3] = skin -> Corners.Count(); skin -> Corners.Insert(texCornerMinY_vec[3]);

	unsigned int texCornerMaxY[4];
	texCornerMaxY[0] = skin -> Corners.Count(); skin -> Corners.Insert(texCornerMaxY_vec[0]);
	texCornerMaxY[1] = skin -> Corners.Count(); skin -> Corners.Insert(texCornerMaxY_vec[1]);
	texCornerMaxY[2] = skin -> Corners.Count(); skin -> Corners.Insert(texCornerMaxY_vec[2]);
	texCornerMaxY[3] = skin -> Corners.Count(); skin -> Corners.Insert(texCornerMaxY_vec[3]);

	off0 += 0;
	off1 += 4;
	polyhedra -> Insert_Corn(-scale.X, -scale.Y, -FrameSizeOut.Z);
	polyhedra -> Insert_Corn(+scale.X, -scale.Y, -FrameSizeOut.Z);
	polyhedra -> Insert_Corn(+scale.X, +scale.Y, -FrameSizeOut.Z);
	polyhedra -> Insert_Corn(-scale.X, +scale.Y, -FrameSizeOut.Z);
	polyhedra -> Insert_Face4(off0 + 0, off0 + 1, off1 + 0, off1 + 1);
	polyhedra -> Insert_Face4(off0 + 1, off0 + 2, off1 + 1, off1 + 2);
	polyhedra -> Insert_Face4(off0 + 2, off0 + 3, off1 + 2, off1 + 3);
	polyhedra -> Insert_Face4(off0 + 3, off0 + 0, off1 + 3, off1 + 0);
	skin -> Insert_Face4(texMiddleInnX[0], texMiddleInnX[1], texMiddleInnX[2], texMiddleInnX[3]);
	skin -> Insert_Face4(texMiddleInnY[0], texMiddleInnY[1], texMiddleInnY[2], texMiddleInnY[3]);
	skin -> Insert_Face4(texMiddleInnX[0], texMiddleInnX[1], texMiddleInnX[2], texMiddleInnX[3]);
	skin -> Insert_Face4(texMiddleInnY[0], texMiddleInnY[1], texMiddleInnY[2], texMiddleInnY[3]);

	off0 += 4;
	off1 += 4;
	polyhedra -> Insert_Corn(-scale.X - FrameSizeOut.X, -scale.Y - FrameSizeOut.Y, -FrameSizeOut.Z);
	polyhedra -> Insert_Corn(-scale.X,                  -scale.Y - FrameSizeOut.Y, -FrameSizeOut.Z);
	polyhedra -> Insert_Corn(+scale.X,                  -scale.Y - FrameSizeOut.Y, -FrameSizeOut.Z);
	polyhedra -> Insert_Corn(+scale.X + FrameSizeOut.X, -scale.Y - FrameSizeOut.Y, -FrameSizeOut.Z);
	polyhedra -> Insert_Corn(+scale.X + FrameSizeOut.X, -scale.Y,                  -FrameSizeOut.Z);
	polyhedra -> Insert_Corn(+scale.X + FrameSizeOut.X, +scale.Y,                  -FrameSizeOut.Z);
	polyhedra -> Insert_Corn(+scale.X + FrameSizeOut.X, +scale.Y + FrameSizeOut.Y, -FrameSizeOut.Z);
	polyhedra -> Insert_Corn(+scale.X,                  +scale.Y + FrameSizeOut.Y, -FrameSizeOut.Z);
	polyhedra -> Insert_Corn(-scale.X,                  +scale.Y + FrameSizeOut.Y, -FrameSizeOut.Z);
	polyhedra -> Insert_Corn(-scale.X - FrameSizeOut.X, +scale.Y + FrameSizeOut.Y, -FrameSizeOut.Z);
	polyhedra -> Insert_Corn(-scale.X - FrameSizeOut.X, +scale.Y,                  -FrameSizeOut.Z);
	polyhedra -> Insert_Corn(-scale.X - FrameSizeOut.X, -scale.Y,                  -FrameSizeOut.Z);
	polyhedra -> Insert_Face3(off0 +  0, off1 +  1, off1 +  0);
	polyhedra -> Insert_Face4(off0 +  0, off0 +  1, off1 +  1, off1 + 2);
	polyhedra -> Insert_Face3(off1 +  2, off0 +  1, off1 +  3);
	polyhedra -> Insert_Face3(off0 +  1, off1 +  4, off1 +  3);
	polyhedra -> Insert_Face4(off0 +  1, off0 +  2, off1 +  4, off1 + 5);
	polyhedra -> Insert_Face3(off1 +  5, off0 +  2, off1 +  6);
	polyhedra -> Insert_Face3(off0 +  2, off1 +  7, off1 +  6);
	polyhedra -> Insert_Face4(off0 +  2, off0 +  3, off1 +  7, off1 + 8);
	polyhedra -> Insert_Face3(off1 +  8, off0 +  3, off1 +  9);
	polyhedra -> Insert_Face3(off0 +  3, off1 + 10, off1 +  9);
	polyhedra -> Insert_Face4(off0 +  3, off0 +  0, off1 + 10, off1 + 11);
	polyhedra -> Insert_Face3(off1 + 11, off0 +  0, off1 + 00);
	skin -> Insert_Face3(texCornerMinX[1], texCornerMinX[3], texCornerMinX[2]);
	skin -> Insert_Face4(texMiddleOutX[0], texMiddleOutX[1], texMiddleOutX[2], texMiddleOutX[3]);
	skin -> Insert_Face3(texCornerMaxX[2], texCornerMaxX[0], texCornerMaxX[3]);
	skin -> Insert_Face3(texCornerMinY[1], texCornerMinY[3], texCornerMinY[2]);
	skin -> Insert_Face4(texMiddleOutY[0], texMiddleOutY[1], texMiddleOutY[2], texMiddleOutY[3]);
	skin -> Insert_Face3(texCornerMaxY[2], texCornerMaxY[0], texCornerMaxY[3]);
	skin -> Insert_Face3(texCornerMinX[1], texCornerMinX[3], texCornerMinX[2]);
	skin -> Insert_Face4(texMiddleOutX[0], texMiddleOutX[1], texMiddleOutX[2], texMiddleOutX[3]);
	skin -> Insert_Face3(texCornerMaxX[2], texCornerMaxX[0], texCornerMaxX[3]);
	skin -> Insert_Face3(texCornerMinY[1], texCornerMinY[3], texCornerMinY[2]);
	skin -> Insert_Face4(texMiddleOutY[0], texMiddleOutY[1], texMiddleOutY[2], texMiddleOutY[3]);
	skin -> Insert_Face3(texCornerMaxY[2], texCornerMaxY[0], texCornerMaxY[3]);

	off0 += 4;
	off1 += 12;
	polyhedra -> Insert_Corn(-scale.X - FrameSizeOut.X, -scale.Y - FrameSizeOut.Y, +FrameSizeOut.Z);
	polyhedra -> Insert_Corn(-scale.X,                  -scale.Y - FrameSizeOut.Y, +FrameSizeOut.Z);
	polyhedra -> Insert_Corn(+scale.X,                  -scale.Y - FrameSizeOut.Y, +FrameSizeOut.Z);
	polyhedra -> Insert_Corn(+scale.X + FrameSizeOut.X, -scale.Y - FrameSizeOut.Y, +FrameSizeOut.Z);
	polyhedra -> Insert_Corn(+scale.X + FrameSizeOut.X, -scale.Y,                  +FrameSizeOut.Z);
	polyhedra -> Insert_Corn(+scale.X + FrameSizeOut.X, +scale.Y,                  +FrameSizeOut.Z);
	polyhedra -> Insert_Corn(+scale.X + FrameSizeOut.X, +scale.Y + FrameSizeOut.Y, +FrameSizeOut.Z);
	polyhedra -> Insert_Corn(+scale.X,                  +scale.Y + FrameSizeOut.Y, +FrameSizeOut.Z);
	polyhedra -> Insert_Corn(-scale.X,                  +scale.Y + FrameSizeOut.Y, +FrameSizeOut.Z);
	polyhedra -> Insert_Corn(-scale.X - FrameSizeOut.X, +scale.Y + FrameSizeOut.Y, +FrameSizeOut.Z);
	polyhedra -> Insert_Corn(-scale.X - FrameSizeOut.X, +scale.Y,                  +FrameSizeOut.Z);
	polyhedra -> Insert_Corn(-scale.X - FrameSizeOut.X, -scale.Y,                  +FrameSizeOut.Z);
	polyhedra -> Insert_Face4(off0 + 0x0, off0 + 0x1, off1 + 0x0, off1 + 0x1);
	polyhedra -> Insert_Face4(off0 + 0x1, off0 + 0x2, off1 + 0x1, off1 + 0x2);
	polyhedra -> Insert_Face4(off0 + 0x2, off0 + 0x3, off1 + 0x2, off1 + 0x3);
	polyhedra -> Insert_Face4(off0 + 0x3, off0 + 0x4, off1 + 0x3, off1 + 0x4);
	polyhedra -> Insert_Face4(off0 + 0x4, off0 + 0x5, off1 + 0x4, off1 + 0x5);
	polyhedra -> Insert_Face4(off0 + 0x5, off0 + 0x6, off1 + 0x5, off1 + 0x6);
	polyhedra -> Insert_Face4(off0 + 0x6, off0 + 0x7, off1 + 0x6, off1 + 0x7);
	polyhedra -> Insert_Face4(off0 + 0x7, off0 + 0x8, off1 + 0x7, off1 + 0x8);
	polyhedra -> Insert_Face4(off0 + 0x8, off0 + 0x9, off1 + 0x8, off1 + 0x9);
	polyhedra -> Insert_Face4(off0 + 0x9, off0 + 0xA, off1 + 0x9, off1 + 0xA);
	polyhedra -> Insert_Face4(off0 + 0xA, off0 + 0xB, off1 + 0xA, off1 + 0xB);
	polyhedra -> Insert_Face4(off0 + 0xB, off0 + 0x0, off1 + 0xB, off1 + 0x0);
	skin -> Insert_Face4(texCornerMinX[0], texCornerMinX[1], texCornerMinX[2], texCornerMinX[3]);
	skin -> Insert_Face4(texMiddleOutX[0], texMiddleOutX[1], texMiddleOutX[2], texMiddleOutX[3]);
	skin -> Insert_Face4(texCornerMaxX[0], texCornerMaxX[1], texCornerMaxX[2], texCornerMaxX[3]);
	skin -> Insert_Face4(texCornerMinY[0], texCornerMinY[1], texCornerMinY[2], texCornerMinY[3]);
	skin -> Insert_Face4(texMiddleOutY[0], texMiddleOutY[1], texMiddleOutY[2], texMiddleOutY[3]);
	skin -> Insert_Face4(texCornerMaxY[0], texCornerMaxY[1], texCornerMaxY[2], texCornerMaxY[3]);
	skin -> Insert_Face4(texCornerMinX[0], texCornerMinX[1], texCornerMinX[2], texCornerMinX[3]);
	skin -> Insert_Face4(texMiddleOutX[0], texMiddleOutX[1], texMiddleOutX[2], texMiddleOutX[3]);
	skin -> Insert_Face4(texCornerMaxX[0], texCornerMaxX[1], texCornerMaxX[2], texCornerMaxX[3]);
	skin -> Insert_Face4(texCornerMinY[0], texCornerMinY[1], texCornerMinY[2], texCornerMinY[3]);
	skin -> Insert_Face4(texMiddleOutY[0], texMiddleOutY[1], texMiddleOutY[2], texMiddleOutY[3]);
	skin -> Insert_Face4(texCornerMaxY[0], texCornerMaxY[1], texCornerMaxY[2], texCornerMaxY[3]);

	off0 += 12;
	off1 += 12;
	polyhedra -> Insert_Corn(-scale.X, -scale.Y, +FrameSizeOut.Z);
	polyhedra -> Insert_Corn(+scale.X, -scale.Y, +FrameSizeOut.Z);
	polyhedra -> Insert_Corn(+scale.X, +scale.Y, +FrameSizeOut.Z);
	polyhedra -> Insert_Corn(-scale.X, +scale.Y, +FrameSizeOut.Z);
	polyhedra -> Insert_Face3(off1 + 0, off0 + 0, off0 + 1);
	polyhedra -> Insert_Face4(off1 + 1, off1 + 0, off0 + 2, off0 + 1);
	polyhedra -> Insert_Face3(off0 + 3, off1 + 1, off0 + 2);
	polyhedra -> Insert_Face3(off1 + 1, off0 + 3, off0 + 4);
	polyhedra -> Insert_Face4(off1 + 2, off1 + 1, off0 + 5, off0 + 4);
	polyhedra -> Insert_Face3(off0 + 6, off1 + 2, off0 + 5);
	polyhedra -> Insert_Face3(off1 + 2, off0 + 6, off0 + 7);
	polyhedra -> Insert_Face4(off1 + 3, off1 + 2, off0 + 8, off0 + 7);
	polyhedra -> Insert_Face3(off0 + 9, off1 + 3, off0 + 8);
	polyhedra -> Insert_Face3(off1 + 3, off0 + 9, off0 + 10);
	polyhedra -> Insert_Face4(off1 + 0, off1 + 3, off0 + 11, off0 + 10);
	polyhedra -> Insert_Face3(off0 + 0, off1 + 0, off0 + 11);
	skin -> Insert_Face3(texCornerMinX[3], texCornerMinX[0], texCornerMinX[1]);
	skin -> Insert_Face4(texMiddleOutX[3], texMiddleOutX[2], texMiddleOutX[1], texMiddleOutX[0]);
	skin -> Insert_Face3(texCornerMaxX[1], texCornerMaxX[2], texCornerMaxX[0]);
	skin -> Insert_Face3(texCornerMinY[3], texCornerMinY[0], texCornerMinY[1]);
	skin -> Insert_Face4(texMiddleOutY[3], texMiddleOutY[2], texMiddleOutY[1], texMiddleOutY[0]);
	skin -> Insert_Face3(texCornerMaxY[1], texCornerMaxY[2], texCornerMaxY[0]);
	skin -> Insert_Face3(texCornerMinX[3], texCornerMinX[0], texCornerMinX[1]);
	skin -> Insert_Face4(texMiddleOutX[3], texMiddleOutX[2], texMiddleOutX[1], texMiddleOutX[0]);
	skin -> Insert_Face3(texCornerMaxX[1], texCornerMaxX[2], texCornerMaxX[0]);
	skin -> Insert_Face3(texCornerMinY[3], texCornerMinY[0], texCornerMinY[1]);
	skin -> Insert_Face4(texMiddleOutY[3], texMiddleOutY[2], texMiddleOutY[1], texMiddleOutY[0]);
	skin -> Insert_Face3(texCornerMaxY[1], texCornerMaxY[2], texCornerMaxY[0]);

	off0 += 12;
	off1 += 4;
	polyhedra -> Insert_Corn(-scale.X, -scale.Y, +FrameSizeInn.Z);
	polyhedra -> Insert_Corn(+scale.X, -scale.Y, +FrameSizeInn.Z);
	polyhedra -> Insert_Corn(+scale.X, +scale.Y, +FrameSizeInn.Z);
	polyhedra -> Insert_Corn(-scale.X, +scale.Y, +FrameSizeInn.Z);
	polyhedra -> Insert_Face4(off0 + 0, off0 + 1, off1 + 0, off1 + 1);
	polyhedra -> Insert_Face4(off0 + 1, off0 + 2, off1 + 1, off1 + 2);
	polyhedra -> Insert_Face4(off0 + 2, off0 + 3, off1 + 2, off1 + 3);
	polyhedra -> Insert_Face4(off0 + 3, off0 + 0, off1 + 3, off1 + 0);
	skin -> Insert_Face4(texMiddleInnX[0], texMiddleInnX[1], texMiddleInnX[2], texMiddleInnX[3]);
	skin -> Insert_Face4(texMiddleInnY[0], texMiddleInnY[1], texMiddleInnY[2], texMiddleInnY[3]);
	skin -> Insert_Face4(texMiddleInnX[0], texMiddleInnX[1], texMiddleInnX[2], texMiddleInnX[3]);
	skin -> Insert_Face4(texMiddleInnY[0], texMiddleInnY[1], texMiddleInnY[2], texMiddleInnY[3]);

	skin -> Done();
	polyhedra -> Skin = skin;
	Debug::Log << "Polyhedra: Generate: FramedImage: (" << img.W() << "x" << img.H() << ") done" << Debug::Done;
	polyhedra -> Done();
	return polyhedra;
}
