#include "SceneObject/Parsing.hpp"

// FileParsing
#include "FileParsing/TextCommand/Args.hpp"
#include "FileParsing/TextCommand/Exceptions.hpp"
#include "FileParsing/TextCommand/FuncNormal.hpp"

// PolyHedra
#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"
#include "PolyHedra/Manager.hpp"

// NewPolyHedra
#include "Special/Basic3D/Logical/Data.hpp"
#include "Special/Basic3D/Logical/ObjectManager.hpp"

// SceneObject
#include "SceneObject/.hpp"
#include "SceneObject/PolyHedraObject.hpp"
#include "SceneObject/LightAmbient.hpp"
#include "SceneObject/LightDirection.hpp"
#include "SceneObject/LightPoint.hpp"
#include "SceneObject/LightSpot.hpp"

// Debug
#include <iostream>

// Context
#include "Context.hpp"



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



SceneParsingData::SceneParsingData(const FileInfo & file, SceneObject_Manager & manager, Light3DContext & context)
	: TextCommand::Loop()
	, Manager(manager)
	, Context(context)
	, NamedPallets()
{
	File = file;
	NamedPallets.ChangeMissing(NewPolyHedra::PalletManager::sTake(*PolyHedraGenerate::RegularHexaHedron(1.0f)));

	Commands.Insert(new TextCommand::FuncNormal("varFloat",			this, &SceneParsingData::PutFloat));
	Commands.Insert(new TextCommand::FuncNormal("pallet",			this, &SceneParsingData::Parse_Pallet));
	Commands.Insert(new TextCommand::FuncNormal("place",			this, &SceneParsingData::Parse_Place));
	Commands.Insert(new TextCommand::FuncNormal("LightAmbient",		this, &SceneParsingData::Parse_LightAmbient));
	Commands.Insert(new TextCommand::FuncNormal("LightDirectionD",	this, &SceneParsingData::Parse_LightDirectionD));
	Commands.Insert(new TextCommand::FuncNormal("LightPoint",		this, &SceneParsingData::Parse_LightPoint));
	Commands.Insert(new TextCommand::FuncNormal("LightSpotT",		this, &SceneParsingData::Parse_LightSpotT));
}

void SceneParsingData::Parse_Pallet(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 2)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 2"); }

	FileInfo file(File.Directory().File(cmd_args.ToString(0)));

	PolyHedra * polyhedra = PolyHedraManager::sTake_Data(file);
	if (polyhedra == nullptr)
	{
		std::cout << "PolyHedra " << file << " null\n";
		return;
	}

	NamedPallets.Put(cmd_args.ToString(1), NewPolyHedra::PalletManager::sTake(*polyhedra));
}
void SceneParsingData::Parse_Place(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 7)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 7"); }

	NewPolyHedra::Pallet * pallet = NamedPallets.Find_Data(cmd_args.ToString(0));

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

	Manager.Collection.Objects.Insert(new SceneObject_PolyHedraObject(&NewPolyHedra::Basic3D::Manager::Current().TakeDisplayObject(*pallet), trans));
}

#include "Special/TransScaleColor3D/Logical/Object.hpp"
//#include "NewPolyHedra/PalletObjectData.hpp"

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
	obj -> Data.Trans = trans;
	//Context.SceneObject_Manager.Collection.Objects.Insert(obj);
	Manager.Collection.Objects.Insert(obj);
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
	obj -> Data.Trans = trans;
	//Context.SceneObject_Manager.Collection.Objects.Insert(obj);
	Manager.Collection.Objects.Insert(obj);
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
	obj -> Data.Trans = trans;
	//Context.SceneObject_Manager.Collection.Objects.Insert(obj);
	Manager.Collection.Objects.Insert(obj);
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
	obj -> Data.Trans = trans;
	//Context.SceneObject_Manager.Collection.Objects.Insert(obj);
	Manager.Collection.Objects.Insert(obj);
}
