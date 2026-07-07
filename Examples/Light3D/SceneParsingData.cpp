#include "SceneParsingData.hpp"

#include "FileParsing/Text/Exceptions.hpp"
#include "FileParsing/Text/TextCommand.hpp"

#include "Context.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"
#include "SceneObject/PolyHedraObject.hpp"

#include <iostream>



SceneParsingData::ParsingCommand::ParsingCommand(std::string name)
	: Name(name)
{ }

SceneParsingData::~SceneParsingData()
{
	for (unsigned int i = 0; i < Commands.Count(); i++)
	{
		delete Commands[i];
	}
}
SceneParsingData::SceneParsingData(const FileInfo & file, Light3DContext & context)
	: File(file)
	, Context(context)
	, PolyHedras()
{
	//MissingPolyHedra = Context.PolyHedraManager.MakePallet(PolyHedraGenerate::RegularHexaHedron(1.0f));
	MissingPolyHedra = Context.ObjectManagerBasic.FindMakePalletObjectManager(PolyHedraGenerate::RegularHexaHedron(1.0f));

	/* Problem
		some commands like belt have variants
		variants are somewhat normalized
			> <   direction
			0 1   closure
	*/

	ParsingCommand * cmd;
	cmd = new ParsingCommand("varFloat");			cmd -> Func.Assign(&VariableFloats, &ParsingVariable::FloatMemory::Put);	Commands.Insert(cmd);
	cmd = new ParsingCommand("polyhedra");			cmd -> Func.Assign(this, &SceneParsingData::Parse_PolyHedra);				Commands.Insert(cmd);
	cmd = new ParsingCommand("place");				cmd -> Func.Assign(this, &SceneParsingData::Parse_Place);					Commands.Insert(cmd);
	cmd = new ParsingCommand("LightAmbient");		cmd -> Func.Assign(this, &SceneParsingData::Parse_LightAmbient);			Commands.Insert(cmd);
	cmd = new ParsingCommand("LightDirectionD");	cmd -> Func.Assign(this, &SceneParsingData::Parse_LightDirectionD);			Commands.Insert(cmd);
	cmd = new ParsingCommand("LightSpotT");			cmd -> Func.Assign(this, &SceneParsingData::Parse_LightSpotT);				Commands.Insert(cmd);
}

void SceneParsingData::Parse(const TextCommand & cmd)
{
	try
	{
		std::string name = cmd.Name();
		if (name == "")
		{
			return;
		}
		for (unsigned int i = 0; i < Commands.Count(); i++)
		{
			ParsingCommand * cmd_func = Commands[i];
			if (cmd_func -> Name == name)
			{
				cmd_func -> Func(cmd);
				return;
			}
		}
		std::cout << "unknown: " << cmd << '\n';
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
	//PolyHedraPalletManager * manager = Context.PolyHedraManager.MakePallet(polyhedra);
	NewPolyHedra_PalletObjectManager * manager = Context.ObjectManagerBasic.FindMakePalletObjectManager(polyhedra);
	PolyHedras.Insert(manager);
}
void SceneParsingData::Parse_Place(const TextCommand & cmd)
{
	if (!(cmd.Count() == 7)) { throw InvalidCommandArgumentCount(cmd, "n == 7"); }

	std::string name = cmd.ToString(0);
	NewPolyHedra_PalletObjectManager * polyhedra = MissingPolyHedra;
	for (unsigned int i = 0; i < PolyHedras.Count(); i++)
	{
		if (PolyHedras[i] -> Pallet -> Object -> Name == name)
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

#include "NewPolyHedra/DataType/TransScaleColor3D/ObjectData.hpp"
//#include "NewPolyHedra/Type/ObjectData.hpp"
#include "NewPolyHedra/PalletObjectData.hpp"

void SceneParsingData::Parse_LightAmbient(const TextCommand & cmd)
{
	if (!(cmd.Count() == 10)) { throw InvalidCommandArgumentCount(cmd, "n == 10"); }

	LightBase * light = Context.TakeLightAmbient();
	if (light == nullptr)
	{
		throw CommandInvalidState(cmd, "All Ambient Lights taken");
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
	obj -> Data.Data.Trans = trans;
	Context.Objects.Insert(obj);
}
void SceneParsingData::Parse_LightDirectionD(const TextCommand & cmd)
{
	if (!(cmd.Count() == 10)) { throw InvalidCommandArgumentCount(cmd, "n == 10"); }

	LightDirection * light = Context.TakeLightSolar();
	if (light == nullptr)
	{
		throw CommandInvalidState(cmd, "All Directional Lights taken");
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
	obj -> Data.Data.Trans = trans;
	Context.Objects.Insert(obj);
}
void SceneParsingData::Parse_LightSpotT(const TextCommand & cmd)
{
	if (!(cmd.Count() == 12)) { throw InvalidCommandArgumentCount(cmd, "n == 12"); }

	LightSpot * light = Context.TakeLightSpot();
	if (light == nullptr)
	{
		throw CommandInvalidState(cmd, "All Spot Lights taken");
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
	obj -> Data.Data.Trans = trans;
	Context.Objects.Insert(obj);
}
