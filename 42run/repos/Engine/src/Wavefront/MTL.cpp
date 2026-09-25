#include "Wavefront/MTL.hpp"

#include "DataShow.hpp"

#include "FileInfo.hpp"
#include "FileParsing/LineCommand.hpp"

#include <string>



Wavefront::MTL::Material::Material()
{

}
std::string Wavefront::MTL::Material::ToString()
{
	std::ostringstream os;
	os << "Name: " << Name;
	os << "\n  Ka: " << Ka;
	os << "\n  Kd: " << Kd;
	os << "\n  Ks: " << Ks;
	os << "\n  Ns: " << Ns;
	os << "\n  Ni: " << Ni;
	os << "\n  d: " << d;
	os << "\n  illum: " << illum;
	return os.str();
}



Wavefront::MTL::MTL()
{
	DefaultMaterial.Ka = ColorF4(0.25, 0.0, 0.0);
	DefaultMaterial.Kd = ColorF4(0.0, 0.0, 0.25);
	DefaultMaterial.Ks = ColorF4(0.0, 0.25, 0.0);
	DefaultMaterial.Ns = 32;

	DefaultMaterial.Ni = 1.0;
	DefaultMaterial.d =  1.0;
	DefaultMaterial.Tr = 0.0;
	DefaultMaterial.illum = 2;

	Index_Newest = 0xFFFFFFFF;
	Index_Selected = 0xFFFFFFFF;
}
Wavefront::MTL::~MTL()
{

}



Wavefront::MTL::Material * Wavefront::MTL::Newest()
{
	if (Index_Newest != 0xFFFFFFFF)
	{
		return &Materials[Index_Newest];
	}
	return NULL;
}
Wavefront::MTL::Material & Wavefront::MTL::Index(unsigned int idx)
{
	if (idx != 0xFFFFFFFF)
	{
		return Materials[idx];
	}
	return DefaultMaterial;
}

void Wavefront::MTL::Insert(MTL & mtl)
{
	//Materials.Insert((Material*)mtl.Materials.Data(), mtl.Materials.Count());
	Materials.Insert(mtl.Materials);
}
void Wavefront::MTL::Select(std::string name)
{
	for (unsigned int i = 0; i < Materials.Count(); i++)
	{
		if (Materials[i].Name == name)
		{
			Index_Selected = i;
			return;
		}
	}
	Index_Selected = 0xFFFFFFFF;
}



void Wavefront::MTL::Parse_newmtl(const LineCommand & cmd)
{
	Index_Newest = Materials.Count();
	Materials.Insert(DefaultMaterial);
	Newest() -> Name = cmd.Args[0];
}

void Wavefront::MTL::Parse_Ka(const LineCommand & cmd)
{
	Newest() -> Ka.R = std::stof(cmd.Args[0]);
	Newest() -> Ka.G = std::stof(cmd.Args[1]);
	Newest() -> Ka.B = std::stof(cmd.Args[2]);
}
void Wavefront::MTL::Parse_Kd(const LineCommand & cmd)
{
	Newest() -> Kd.R = std::stof(cmd.Args[0]);
	Newest() -> Kd.G = std::stof(cmd.Args[1]);
	Newest() -> Kd.B = std::stof(cmd.Args[2]);
}
void Wavefront::MTL::Parse_Ks(const LineCommand & cmd)
{
	Newest() -> Ks.R = std::stof(cmd.Args[0]);
	Newest() -> Ks.G = std::stof(cmd.Args[1]);
	Newest() -> Ks.B = std::stof(cmd.Args[2]);
}
void Wavefront::MTL::Parse_Ns(const LineCommand & cmd)
{
	Newest() -> Ns = std::stof(cmd.Args[0]);
}
void Wavefront::MTL::Parse_Ni(const LineCommand & cmd)
{
	Newest() -> Ni = std::stof(cmd.Args[0]);
	if (Newest() -> Ni != 1.0f)
	{
		std::cout << "Ni values other then 1.0 are currently not Implemented.\n";
	}
}
void Wavefront::MTL::Parse_d(const LineCommand & cmd)
{
	Newest() -> d = std::stof(cmd.Args[0]);
	if (Newest() -> d != 1.0f)
	{
		std::cout << "d values other then 1.0 are currently not Implemented.\n";
	}
}

void Wavefront::MTL::Parse_illum(const LineCommand & cmd)
{
	Newest() -> illum = std::stoi(cmd.Args[0]);
	if (Newest() -> illum != 2)
	{
		std::cout << "illum values other then 2 are currently not Implemented.\n";
	}
}

void Wavefront::MTL::Parse(const LineCommand & cmd)
{
	if (cmd.Name.empty())			{ }
	else if (cmd.Name == "#")		{ }
	else if (cmd.Name == "newmtl")	{ Parse_newmtl(cmd); }
	else if (cmd.Name == "Ka")		{ Parse_Ka(cmd); }
	else if (cmd.Name == "Kd")		{ Parse_Kd(cmd); }
	else if (cmd.Name == "Ks")		{ Parse_Ks(cmd); }
	else if (cmd.Name == "Ns")		{ Parse_Ns(cmd); }
	else if (cmd.Name == "Ni")		{ Parse_Ni(cmd); }
	else if (cmd.Name == "d")		{ Parse_d(cmd); }
	else if (cmd.Name == "illum")	{ Parse_illum(cmd); }
	else
	{
		std::cout << "Unknown MTL LineCommand: '" << cmd.Name << "'\n";
	}
}



Wavefront::MTL * Wavefront::MTL::Load(const FileInfo & file)
{
	if (file.Exists())
	{
		if (file.Extension() != ".mtl")
		{
			std::cout << "\e[38;2;255;000;000m" << "Warnign: " << file.Path << " is being loaded as MTL but does not have .mtl extension.\n" << "\e[m";
		}
		MTL * mtl = new MTL();
		LineCommand::Split(file, *mtl, &MTL::Parse);
		return mtl;
	}
	return NULL;
}
