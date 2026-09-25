#include "Wavefront/OBJ.hpp"
#include "Wavefront/Main/Data.hpp"
#include "Wavefront/MTL.hpp"

#include "FileInfo.hpp"
#include "FileParsing/LineCommand.hpp"

#include "ValueType/Vector/F2.hpp"
#include "ValueType/Box/F3.hpp"
#include "Display/SizeRatio2D.hpp"

#include "DataShow.hpp"

#include <string>
#include <math.h>



Wavefront::OBJ::FaceCorner::FaceCorner()
{
	Position = 0xFFFFFFFF;
	Texture = 0xFFFFFFFF;
	Normal = 0xFFFFFFFF;
}
Wavefront::OBJ::Face::Face()
{
	Corner1 = FaceCorner();
	Corner2 = FaceCorner();
	Corner3 = FaceCorner();
}



Wavefront::OBJ::OBJ()
{ }
Wavefront::OBJ::~OBJ()
{ }



static char SizeMax(VectorF3 val)
{
	if (val.X > val.Y && val.X > val.Z) { return 0b001; }
	if (val.Y > val.Z && val.Y > val.X) { return 0b010; }
	if (val.Z > val.X && val.Z > val.Y) { return 0b100; }
	return 0;
}
static char SizeMid(VectorF3 val)
{
	if ((val.X > val.Y && val.X < val.Z) || (val.X < val.Y && val.X > val.Z)) { return 0b001; }
	if ((val.Y > val.X && val.Y < val.Z) || (val.Y < val.X && val.Y > val.Z)) { return 0b010; }
	if ((val.Z > val.X && val.Z < val.Y) || (val.Z < val.X && val.Z > val.Y)) { return 0b100; }
	return 0;
}

VectorF4 Wavefront::OBJ::Position_MainData(unsigned int idx)
{
	return Positions[idx];
}
VectorF3 Wavefront::OBJ::Texture_MainData(unsigned int idx, VectorF4 pos, SizeRatio2D scale, char sides)
{
	if (idx != 0xFFFFFFFF)
	{
		return Textures[idx];
	}
	else
	{
		VectorF2 tex;
		if (sides == 0b011) { tex = VectorF2(pos.X, -pos.Y); }
		if (sides == 0b101) { tex = VectorF2(pos.X, -pos.Z); }
		if (sides == 0b110) { tex = VectorF2(pos.Z, -pos.Y); }
		return VectorF3(tex.X * scale.Ratio.X, tex.Y * scale.Ratio.Y, 0);
	}
}
VectorF3 Wavefront::OBJ::Normal_MainData(unsigned int idx, VectorF3 normal)
{
	if (idx != 0xFFFFFFFF)
	{
		return Normals[idx];
	}
	else
	{
		return normal;
	}
}
Wavefront::Main::Data * Wavefront::OBJ::ToMainData(int & count, SizeRatio2D texScale)
{
	count = Faces.Count() * 3;
	Main::Data * data = new Main::Data[count];

	VectorF3 TexMin(+INFINITY, +INFINITY, +INFINITY);
	VectorF3 TexMax(-INFINITY, -INFINITY, -INFINITY);
	for (unsigned int i = 0; i < Positions.Count(); i++)
	{
		const VectorF4 & p = Positions[i];
		if (p.X < TexMin.X) { TexMin.X = p.X; }
		if (p.Y < TexMin.Y) { TexMin.Y = p.Y; }
		if (p.Z < TexMin.Z) { TexMin.Z = p.Z; }
		if (p.X > TexMax.X) { TexMax.X = p.X; }
		if (p.Y > TexMax.Y) { TexMax.Y = p.Y; }
		if (p.Y > TexMax.Z) { TexMax.Z = p.Z; }
	}
	VectorF3 TexLen = TexMax - TexMin;
	char sides = SizeMax(TexLen) | SizeMid(TexLen);

	ColorF4 colors [] = {
		ColorF4(0.0f, 0.0f, 0.0f),
		ColorF4(1.0f, 0.0f, 0.0f),
		ColorF4(0.0f, 1.0f, 0.0f),
		ColorF4(0.0f, 0.0f, 1.0f),
		ColorF4(0.0f, 1.0f, 1.0f),
		ColorF4(1.0f, 0.0f, 1.0f),
		ColorF4(1.0f, 1.0f, 0.0f),
		ColorF4(1.0f, 1.0f, 1.0f),
	};
	int color_count = 8;

	for (unsigned int f = 0; f < Faces.Count(); f++)
	{
		const Face & face = Faces[f];
		int c = f * 3;
		Main::Data & c0 = data[c + 0];
		Main::Data & c1 = data[c + 1];
		Main::Data & c2 = data[c + 2];

		c0.Position = Position_MainData(face.Corner1.Position);
		c1.Position = Position_MainData(face.Corner2.Position);
		c2.Position = Position_MainData(face.Corner3.Position);

		c0.Texture = Texture_MainData(face.Corner1.Texture, c0.Position, texScale, sides);
		c1.Texture = Texture_MainData(face.Corner2.Texture, c1.Position, texScale, sides);
		c2.Texture = Texture_MainData(face.Corner3.Texture, c2.Position, texScale, sides);

		VectorF3 n0(c0.Position.X, c0.Position.Y, c0.Position.Z);
		VectorF3 n1(c1.Position.X, c1.Position.Y, c1.Position.Z);
		VectorF3 n2(c2.Position.X, c2.Position.Y, c2.Position.Z);
		VectorF3 normal = VectorF3::cross(n1 - n0, n2 - n0).normalize();

		c0.Normal = Normal_MainData(face.Corner1.Normal, normal);
		c1.Normal = Normal_MainData(face.Corner2.Normal, normal);
		c2.Normal = Normal_MainData(face.Corner3.Normal, normal);

		ColorF4 col = colors[(f % color_count)];
		c0.Color = col;
		c1.Color = col;
		c2.Color = col;

		const MTL::Material & material = Materials.Index(face.MaterialIndex);

		c0.AmbientColor = material.Ka;
		c0.DiffuseColor = material.Kd;
		c0.SpecularPower = material.Ns;
		c0.SpecularColor = material.Ks;

		c1.AmbientColor = material.Ka;
		c1.DiffuseColor = material.Kd;
		c1.SpecularPower = material.Ns;
		c1.SpecularColor = material.Ks;

		c2.AmbientColor = material.Ka;
		c2.DiffuseColor = material.Kd;
		c2.SpecularPower = material.Ns;
		c2.SpecularColor = material.Ks;
	}

	return data;
}



void Wavefront::OBJ::Parse_v(const LineCommand & cmd)
{
	VectorF4 p;
	if (cmd.Args.size() == 3)
	{
		p.X = std::stof(cmd.Args[0]);
		p.Y = std::stof(cmd.Args[1]);
		p.Z = std::stof(cmd.Args[2]);
		p.W = 1.0f;
	}
	else { std::cout << "Bad Num of Args\n"; }
	//std::cout << "v" << p << "\n";
	Positions.Insert(p);
}
void Wavefront::OBJ::Parse_vt(const LineCommand & cmd)
{
	VectorF3 p;
	if (cmd.Args.size() == 2)
	{
		p.X = std::stof(cmd.Args[0]);
		p.Y = std::stof(cmd.Args[1]);
		p.Z = 0.0f;
	}
	else { std::cout << "Bad Num of Args\n"; }
	//std::cout << "vt" << p << "\n";
	Textures.Insert(p);
}
void Wavefront::OBJ::Parse_vn(const LineCommand & cmd)
{
	VectorF3 p;
	if (cmd.Args.size() == 3)
	{
		p.X = std::stof(cmd.Args[0]);
		p.Y = std::stof(cmd.Args[1]);
		p.Z = std::stof(cmd.Args[2]);
	}
	else { std::cout << "Bad Num of Args\n"; }
	//std::cout << "vn" << p << "\n";
	Textures.Insert(p);
}

Wavefront::OBJ::FaceCorner Wavefront::OBJ::Parse_f_element(std::string text)
{
	std::vector<std::string> index_strings;
	{
		std::string index_string;
		std::stringstream stream(text);
		while (std::getline(stream, index_string, '/'))
		{
			index_strings.push_back(index_string);
		}
	}

	FaceCorner corn;
	if (index_strings.size() >= 1)
	{
		corn.Position = std::stoi(index_strings[0]) - 1;
	}
	if (index_strings.size() >= 2 && !index_strings[1].empty())
	{
		corn.Texture = std::stoi(index_strings[1]) - 1;
	}
	if (index_strings.size() >= 3 && !index_strings[2].empty())
	{
		corn.Normal = std::stoi(index_strings[2]) - 1;
	}

	return corn;
}
void Wavefront::OBJ::Parse_f(const LineCommand & cmd)
{
	if (cmd.Args.size() < 3) { std::cout << "Bad Num of Args\n"; }

	std::vector<FaceCorner> corns;
	for (unsigned int i = 0; i < cmd.Args.size(); i++)
	{
		corns.push_back(Parse_f_element(cmd.Args[i]));
	}

	if (corns.size() == 3)
	{
		Face face;

		face.Corner1 = corns[0];
		face.Corner2 = corns[1];
		face.Corner3 = corns[2];
		face.MaterialIndex = Materials.Index_Selected;
		Faces.Insert(face);
	}
	else if (corns.size() == 4)
	{
		Face face;

		face.Corner1 = corns[0];
		face.Corner2 = corns[1];
		face.Corner3 = corns[2];
		face.MaterialIndex = Materials.Index_Selected;
		Faces.Insert(face);

		face.Corner1 = corns[0];
		face.Corner2 = corns[2];
		face.Corner3 = corns[3];
		face.MaterialIndex = Materials.Index_Selected;
		Faces.Insert(face);
	}
	else
	{
		std::cout << "Error: No Polygons with more then 4 sides.\n";
	}
}

void Wavefront::OBJ::Parse_mtllib(const LineCommand & cmd)
{
	if (cmd.Args.size() < 1) { std::cout << "Bad Num of Args\n"; }
	MTL * mtl = MTL::Load(FileInfo((Path + "/" + cmd.Args[0]).c_str()));
	Materials.Insert(*mtl);
	delete mtl;
}
void Wavefront::OBJ::Parse_usemtl(const LineCommand & cmd)
{
	if (cmd.Args.size() < 1) { std::cout << "Bad Num of Args\n"; }
	Materials.Select(cmd.Args[0]);
}

void Wavefront::OBJ::Parse(const LineCommand & cmd)
{
	if (cmd.Name.empty())			{ }
	else if (cmd.Name == "#")		{ }
	else if (cmd.Name == "v")		{ Parse_v(cmd); }
	else if (cmd.Name == "vt")		{ Parse_vt(cmd); }
	else if (cmd.Name == "vn")		{ Parse_vn(cmd); }
	else if (cmd.Name == "f")		{ Parse_f(cmd); }
	else if (cmd.Name == "mtllib")	{ Parse_mtllib(cmd); }
	else if (cmd.Name == "usemtl")	{ Parse_usemtl(cmd); }
	else
	{
		std::cout << "Unknown OBJ LineCommand: '" << cmd.Name << "'\n";
	}
}



Wavefront::OBJ * Wavefront::OBJ::Load(const FileInfo & file)
{
	if (file.Exists())
	{
		if (file.Extension() != ".obj")
		{
			std::cout << "\e[38;2;255;000;000m" << "Warnign: " << file.Path << " is being loaded as OBJ but does not have .obj extension.\n" << "\e[m";
		}

		OBJ * obj = new OBJ();
		obj -> Path = file.DirectoryString();
		LineCommand::Split(file, *obj, &OBJ::Parse);
		std::cout << "Materials:\n";
		for (unsigned int i = 0; i < obj -> Materials.Materials.Count(); i++)
		{
			std::cout << obj -> Materials.Materials[i].ToString() << "\n";
		}
		return obj;
	}
	return NULL;
}



BoxF3 Wavefront::OBJ::ToAxisBox()
{
	BoxF3 box;

	for (unsigned int i = 0; i < Positions.Count(); i++)
	{
		const VectorF4 & p = Positions[i];
		box.Consider(VectorF3(p.X, p.Y, p.Z));
	}

	return box;
}
