#include "SceneParsingData.hpp"

#include "FileParsing/TextCommand/Args.hpp"
#include "FileParsing/TextCommand/Exceptions.hpp"

#include "Context.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"
#include "PolyHedra/FileCollection.hpp"

#include "SceneObject/SceneObject.hpp"
#include "SceneObject/PolyHedraObject.hpp"
#include "SceneObject/LightAmbient.hpp"
#include "SceneObject/LightDirection.hpp"
#include "SceneObject/LightPoint.hpp"
#include "SceneObject/LightSpot.hpp"

#include <iostream>



SceneParsingData::ParsingCommand::ParsingCommand(std::string name)
	: Name(name)
{ }

template<typename ObjectType>
static void NewParsingCommand(SceneParsingData * parsing, const char * name, ObjectType * obj, void (ObjectType::*func)(const TextCommand::Args &))
{
	SceneParsingData::ParsingCommand * cmd_func;
	cmd_func = new SceneParsingData::ParsingCommand(name);
	cmd_func -> Func.Assign(obj, func);
	parsing -> Commands.Insert(cmd_func);
}



void SceneParsingData::PutFloat(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 2)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 2"); }

	VariableFloats.Put(cmd_args.ToString(0), cmd_args.ToFloat(1));
}
float SceneParsingData::ToFloat(const TextCommand::Args & cmd_args, unsigned int idx) const
{
	std::string str = cmd_args.ToString(idx);
	if (ParsingVariable::Float::IsLiteral(str))
	{
		return ParsingVariable::Float::ParseLiteral(str);
	}
	char sign = ParsingVariable::Float::SignTake(str);
	float value = VariableFloats.To(str);
	return ParsingVariable::Float::SignPut(value, sign);
}



SceneParsingData::~SceneParsingData()
{
	for (unsigned int i = 0; i < Commands.Count(); i++)
	{
		delete Commands[i];
	}
}
SceneParsingData::SceneParsingData(const FileInfo & file, Light3DContext & context, ::PolyHedraFileCollection & file_collection)
	: File(file)
	, Context(context)
	, PolyHedraFileCollection(file_collection)
	, PolyHedras()
{
	MissingPolyHedra = Context.ObjectManagerBasic.FindMakePalletObjectManager(PolyHedraGenerate::RegularHexaHedron(1.0f));

	/* Problem
		some commands like belt have variants
		variants are somewhat normalized
			> <   direction
			0 1   closure
	*/

	NewParsingCommand(this, "varFloat",			this, &SceneParsingData::PutFloat);
	NewParsingCommand(this, "pallet",			this, &SceneParsingData::Parse_Pallet);
	NewParsingCommand(this, "place",			this, &SceneParsingData::Parse_Place);
	NewParsingCommand(this, "LightAmbient",		this, &SceneParsingData::Parse_LightAmbient);
	NewParsingCommand(this, "LightDirectionD",	this, &SceneParsingData::Parse_LightDirectionD);
	NewParsingCommand(this, "LightPoint",		this, &SceneParsingData::Parse_LightPoint);
	NewParsingCommand(this, "LightSpotT",		this, &SceneParsingData::Parse_LightSpotT);
}

void SceneParsingData::Parse(const TextCommand::Args & cmd_args)
{
	try
	{
		std::string name = cmd_args.Name();
		if (name == "")
		{
			return;
		}
		for (unsigned int i = 0; i < Commands.Count(); i++)
		{
			ParsingCommand * cmd_func = Commands[i];
			if (cmd_func -> Name == name)
			{
				cmd_func -> Func(cmd_args);
				return;
			}
		}
		throw TextCommand::Exception::Unknown(cmd_args);
	}
	catch (std::exception & ex)
	{
		std::cout << "Exception while Parsing Scene: " << ex.what() << '\n';
		std::cout << "Exception on TextCommand: " << cmd_args << '\n';
	}
}

void SceneParsingData::Parse_Pallet(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 2)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 2"); }

	FileInfo file((File.DirectoryString() + "/" + cmd_args.ToString(0)).c_str());

//	PolyHedra * polyhedra = PolyHedra::Load(file);
	PolyHedra * polyhedra = PolyHedraFileCollection.FindMake(file);

	NewPolyHedra::Pallet * pallet = Context.PalletManager.FindMakePallet(polyhedra);
	pallet -> Name = cmd_args.ToString(1);

	NewPolyHedra::PalletObjectManager * manager = Context.ObjectManagerBasic.FindMakePalletObjectManager(pallet);
	PolyHedras.Insert(manager);
}
void SceneParsingData::Parse_Place(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 7)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 7"); }

	std::string name = cmd_args.ToString(0);
	NewPolyHedra::PalletObjectManager * polyhedra = MissingPolyHedra;
	for (unsigned int i = 0; i < PolyHedras.Count(); i++)
	{
		if (PolyHedras[i] -> Pallet -> Name == name)
		{
			polyhedra = PolyHedras[i];
		}
	}

	Trans3D trans(
		VectorF3(
			ToFloat(cmd_args, 1),
			ToFloat(cmd_args, 2),
			ToFloat(cmd_args, 3)
		),
		EulerAngle3D::Degrees(
			ToFloat(cmd_args, 4),
			ToFloat(cmd_args, 5),
			ToFloat(cmd_args, 6)
		)
	);

	Context.Collection.Objects.Insert(new SceneObject_PolyHedraObject(polyhedra, trans));
}

#include "NewPolyHedra/DataType/TransScaleColor3D/ObjectData.hpp"
#include "NewPolyHedra/PalletObjectData.hpp"

void SceneParsingData::Parse_LightAmbient(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 10)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 10"); }

	LightBase * light = Context.LightManager.TakeAmbient();
	if (light == nullptr)
	{
		throw TextCommand::Exception::InvalidState(cmd_args, "All Ambient Lights taken");
	}
	light -> Intensity = cmd_args.ToFloat(0);
	light -> Color.R = cmd_args.ToFloat(1);
	light -> Color.G = cmd_args.ToFloat(2);
	light -> Color.B = cmd_args.ToFloat(3);

	Trans3D trans;
	trans.Position.X = cmd_args.ToFloat(4);
	trans.Position.Y = cmd_args.ToFloat(5);
	trans.Position.Z = cmd_args.ToFloat(6);
	trans.Rotation.Z0 = Angle::Degrees(cmd_args.ToFloat(7));
	trans.Rotation.X1 = Angle::Degrees(cmd_args.ToFloat(8));
	trans.Rotation.Y2 = Angle::Degrees(cmd_args.ToFloat(9));

	SceneObject_LightAmbient * obj = new SceneObject_LightAmbient();
	obj -> Light = light;
	obj -> Data.Data.Trans = trans;
	Context.Collection.Objects.Insert(obj);
}
void SceneParsingData::Parse_LightDirectionD(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 10)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 10"); }

	LightDirection * light = Context.LightManager.TakeDirection();
	if (light == nullptr)
	{
		throw TextCommand::Exception::InvalidState(cmd_args, "All Directional Lights taken");
	}
	light -> Base.Intensity = cmd_args.ToFloat(0);
	light -> Base.Color.R = cmd_args.ToFloat(1);
	light -> Base.Color.G = cmd_args.ToFloat(2);
	light -> Base.Color.B = cmd_args.ToFloat(3);
	light -> Dir.X = cmd_args.ToFloat(4);
	light -> Dir.Y = cmd_args.ToFloat(5);
	light -> Dir.Z = cmd_args.ToFloat(6);

	Trans3D trans;
	trans.Position.X = cmd_args.ToFloat(7);
	trans.Position.Y = cmd_args.ToFloat(8);
	trans.Position.Z = cmd_args.ToFloat(9);

	SceneObject_LightDirection * obj = new SceneObject_LightDirection();
	obj -> Light = light;
	obj -> Data.Data.Trans = trans;
	Context.Collection.Objects.Insert(obj);
}
void SceneParsingData::Parse_LightPoint(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 10)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 10"); }

	LightPoint * light = Context.LightManager.TakePoint();
	if (light == nullptr)
	{
		throw TextCommand::Exception::InvalidState(cmd_args, "All Point Lights taken");
	}
	light -> Base.Intensity = cmd_args.ToFloat(0);
	light -> Base.Color.R = cmd_args.ToFloat(1);
	light -> Base.Color.G = cmd_args.ToFloat(2);
	light -> Base.Color.B = cmd_args.ToFloat(3);
	light -> Pos.X = cmd_args.ToFloat(4);
	light -> Pos.Y = cmd_args.ToFloat(5);
	light -> Pos.Z = cmd_args.ToFloat(6);

	Trans3D trans;
	trans.Rotation.Z0 = Angle::Degrees(cmd_args.ToFloat(7));
	trans.Rotation.X1 = Angle::Degrees(cmd_args.ToFloat(8));
	trans.Rotation.Y2 = Angle::Degrees(cmd_args.ToFloat(9));

	SceneObject_LightPoint * obj = new SceneObject_LightPoint();
	obj -> Light = light;
	obj -> Data.Data.Trans = trans;
	Context.Collection.Objects.Insert(obj);
}
void SceneParsingData::Parse_LightSpotT(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 12)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 12"); }

	LightSpot * light = Context.LightManager.TakeSpot();
	if (light == nullptr)
	{
		throw TextCommand::Exception::InvalidState(cmd_args, "All Spot Lights taken");
	}
	light -> Base.Intensity = cmd_args.ToFloat(0);
	light -> Base.Color.R = cmd_args.ToFloat(1);
	light -> Base.Color.G = cmd_args.ToFloat(2);
	light -> Base.Color.B = cmd_args.ToFloat(3);
	light -> Range = RangeF(cmd_args.ToFloat(10), cmd_args.ToFloat(11));

	light -> Pos.X = cmd_args.ToFloat(4);
	light -> Pos.Y = cmd_args.ToFloat(5);
	light -> Pos.Z = cmd_args.ToFloat(6);
	light -> Dir.X = cmd_args.ToFloat(7) - (light -> Pos.X);
	light -> Dir.Y = cmd_args.ToFloat(8) - (light -> Pos.Y);
	light -> Dir.Z = cmd_args.ToFloat(9) - (light -> Pos.Z);

	Trans3D trans;

	SceneObject_LightSpot * obj = new SceneObject_LightSpot();
	obj -> Light = light;
	obj -> Data.Data.Trans = trans;
	Context.Collection.Objects.Insert(obj);
}
