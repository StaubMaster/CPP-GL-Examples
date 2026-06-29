#include "SceneParsingData.hpp"

#include "FileParsing/Text/Exceptions.hpp"
#include "FileParsing/Text/TextCommand.hpp"

#include "Context.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"
#include "SceneObject/PolyHedraObject.hpp"

#include <iostream>





SceneParsingData::~SceneParsingData()
{ }
SceneParsingData::SceneParsingData(const FileInfo & file, Light3DContext & context)
	: File(file)
	, Context(context)
	, PolyHedras()
{
	MissingPolyHedra = Context.PolyHedraManager.MakePallet(PolyHedraGenerate::RegularHexaHedron(1.0f));
}

void SceneParsingData::Parse(const TextCommand & cmd)
{
	try
	{
		std::string name = cmd.Name();
		if (name == "") { /*std::cout << "empty\n";*/ }

		else if (name == "varFloat")	{ VariableFloats.Put(cmd); }

		else if (name == "polyhedra")	{ Parse_PolyHedra(cmd); }
		else if (name == "place")		{ Parse_Place(cmd); }

		else if (name == "LightAmbient")		{ Parse_LightAmbient(cmd); }
		else if (name == "LightDirectionD")		{ Parse_LightDirectionD(cmd); }
		else if (name == "LightSpotT")			{ Parse_LightSpotT(cmd); }

		else { std::cout << "unknown: " << cmd << '\n'; }
	}
	catch (std::exception & ex)
	{
		std::cout << "Exception while Parsing Scene: " << ex.what() << '\n';
		std::cout << "Exception on TextCommand: " << cmd << '\n';
	}
}

void SceneParsingData::Parse_PolyHedra(const TextCommand & cmd)
{
	if (!(cmd.Count() == 1)) { throw InvalidCommandArgumentCount(cmd, "n == 1"); }

	FileInfo file((File.DirectoryString() + "/" + cmd.ToString(0)).c_str());
	if (!file.Exists()) { std::cout << cmd.Name() << ": " << "Bad Skin File" << "\n"; return; }
	PolyHedra * polyhedra = PolyHedra::Load(file);
	//polyhedra -> UseCornerNormals = true;
	PolyHedraPalletManager * manager = Context.PolyHedraManager.MakePallet(polyhedra);
	PolyHedras.Insert(manager);
}
void SceneParsingData::Parse_Place(const TextCommand & cmd)
{
	if (!(cmd.Count() == 7)) { throw InvalidCommandArgumentCount(cmd, "n == 7"); }

	std::string name = cmd.ToString(0);
	PolyHedraPalletManager * polyhedra = MissingPolyHedra;
	for (unsigned int i = 0; i < PolyHedras.Count(); i++)
	{
		if (PolyHedras[i] -> Pallet -> Name == name)
		{
			polyhedra = PolyHedras[i];
		}
	}

	Trans3D trans(
		VectorF3(
			VariableFloats.To(cmd, 1),
			VariableFloats.To(cmd, 2),
			VariableFloats.To(cmd, 3)
		),
		EulerAngle3D::Degrees(
			VariableFloats.To(cmd, 4),
			VariableFloats.To(cmd, 5),
			VariableFloats.To(cmd, 6)
		)
	);

	Context.Objects.Insert(new SceneObject_PolyHedraObject(polyhedra, trans));
}

void SceneParsingData::Parse_LightAmbient(const TextCommand & cmd)
{
	if (!(cmd.Count() == 10)) { throw InvalidCommandArgumentCount(cmd, "n == 10"); }

	LightBase * light = Context.TakeLightAmbient();
	if (light == nullptr)
	{
		std::cout << "All Light Ambient taken.";
		return;
	}
	light -> Intensity = cmd.ToFloat(0);
	light -> Color.R = cmd.ToFloat(1);
	light -> Color.G = cmd.ToFloat(2);
	light -> Color.B = cmd.ToFloat(3);

	Trans3D trans;
	trans.Position.X = cmd.ToFloat(4);
	trans.Position.Y = cmd.ToFloat(5);
	trans.Position.Z = cmd.ToFloat(6);
	trans.Rotation.Z0 = Angle::Degrees(cmd.ToFloat(7));
	trans.Rotation.X1 = Angle::Degrees(cmd.ToFloat(8));
	trans.Rotation.Y2 = Angle::Degrees(cmd.ToFloat(9));

	SceneObject_LightAmbient * obj = new SceneObject_LightAmbient();
	obj -> Light = light;
	obj -> Data.Trans = trans;
	Context.Objects.Insert(obj);
}
void SceneParsingData::Parse_LightDirectionD(const TextCommand & cmd)
{
	if (!(cmd.Count() == 10)) { throw InvalidCommandArgumentCount(cmd, "n == 10"); }

	LightDirection * light = Context.TakeLightSolar();
	if (light == nullptr)
	{
		std::cout << "All Light Ambient taken.";
		return;
	}
	light -> Base.Intensity = cmd.ToFloat(0);
	light -> Base.Color.R = cmd.ToFloat(1);
	light -> Base.Color.G = cmd.ToFloat(2);
	light -> Base.Color.B = cmd.ToFloat(3);
	light -> Dir.X = cmd.ToFloat(4);
	light -> Dir.Y = cmd.ToFloat(5);
	light -> Dir.Z = cmd.ToFloat(6);

	Trans3D trans;
	trans.Position.X = cmd.ToFloat(7);
	trans.Position.Y = cmd.ToFloat(8);
	trans.Position.Z = cmd.ToFloat(9);

	SceneObject_LightDirection * obj = new SceneObject_LightDirection();
	obj -> Light = light;
	obj -> Data.Trans = trans;
	Context.Objects.Insert(obj);
}
void SceneParsingData::Parse_LightSpotT(const TextCommand & cmd)
{
	if (!(cmd.Count() == 12)) { throw InvalidCommandArgumentCount(cmd, "n == 12"); }

	LightSpot * light = Context.TakeLightSpot();
	if (light == nullptr)
	{
		std::cout << "All Light Ambient taken.";
		return;
	}
	light -> Base.Intensity = cmd.ToFloat(0);
	light -> Base.Color.R = cmd.ToFloat(1);
	light -> Base.Color.G = cmd.ToFloat(2);
	light -> Base.Color.B = cmd.ToFloat(3);
	light -> Range = RangeF(cmd.ToFloat(10), cmd.ToFloat(11));

	light -> Pos.X = cmd.ToFloat(4);
	light -> Pos.Y = cmd.ToFloat(5);
	light -> Pos.Z = cmd.ToFloat(6);
	light -> Dir.X = cmd.ToFloat(7) - (light -> Pos.X);
	light -> Dir.Y = cmd.ToFloat(8) - (light -> Pos.Y);
	light -> Dir.Z = cmd.ToFloat(9) - (light -> Pos.Z);

	Trans3D trans;

	SceneObject_LightSpot * obj = new SceneObject_LightSpot();
	obj -> Light = light;
	obj -> Data.Trans = trans;
	Context.Objects.Insert(obj);
}
