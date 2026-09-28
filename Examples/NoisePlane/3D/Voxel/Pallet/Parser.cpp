#include "3D/Voxel/Pallet/Parser.hpp"
#include "3D/Voxel/Pallet/Map.hpp"
#include "3D/Voxel/Pallet.hpp"

// Geometry
# include "3D/Voxel/Pallet/Geometry/Map.hpp"

// FileManager
#include "FileParsing/TextCommand/Args.hpp"
#include "FileParsing/TextCommand/ArgsStream.hpp"
#include "FileParsing/TextCommand/Exceptions.hpp"
#include "FileParsing/TextCommand/FuncNormal.hpp"
#include "DirectoryInfo.hpp"

// ValueType
#include "ValueType/Box/U2.hpp"
#include "ValueType/Box/F2.hpp"

// Axis
#include "Axis/2D/Enums.hpp"

// Debug
#include <iostream>



static Axis2D::Diag StringToAxis2D_Diag(const std::string & str)
{
	if (str == "")				{ throw "Invalid Axis2D::Diag String"; }
	else if (str == "Normal0")	{ return Axis2D::Diag::Normal0; }
	else if (str == "Invert0")	{ return Axis2D::Diag::Invert0; }
	else if (str == "Normal1")	{ return Axis2D::Diag::Normal1; }
	else if (str == "Invert1")	{ return Axis2D::Diag::Invert1; }
	else						{ throw "Invalid Axis2D::Diag String"; }
}
static Axis2D::Flip StringToAxis2D_Flip(const std::string & str)
{
	if (str == "")				{ throw "Invalid Axis2D::Flip String"; }
	else if (str == "None")		{ return Axis2D::Flip::None; }
	else if (str == "FlipX")	{ return Axis2D::Flip::FlipX; }
	else if (str == "FlipY")	{ return Axis2D::Flip::FlipY; }
	else						{ throw "Invalid Axis2D::Flip String"; }
}



VoxelPalletMapParser::VoxelPalletMapParser(VoxelPalletMap & map)
	: TextCommand::Loop()
	, Map(map)
{
	Commands.Insert(new TextCommand::FuncNormal("new",			this, &VoxelPalletMapParser::New));
	Commands.Insert(new TextCommand::FuncNormal("done",			this, &VoxelPalletMapParser::Done));
	Commands.Insert(new TextCommand::FuncNormal("tex",			this, &VoxelPalletMapParser::Texture));
	Commands.Insert(new TextCommand::FuncNormal("orient",		this, &VoxelPalletMapParser::Orientation));
}



void VoxelPalletMapParser::New(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 3)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 3"); }
	if (Entry != nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "Entry not done"); }

	std::string name = cmd_args.ToString(0);
	const VoxelPalletGeometry & geom = VoxelPalletGeometryMap::StaticMap[cmd_args.ToString(1).c_str()];

	VoxelMaterialType material = VoxelMaterialType::None;
	{
		std::string type_str = cmd_args.ToString(2);
		if (type_str == "None")   { material = VoxelMaterialType::None; }
		if (type_str == "Dirt")   { material = VoxelMaterialType::Dirt; }
		if (type_str == "Stone")  { material = VoxelMaterialType::Stone; }
		if (type_str == "Wood" )  { material = VoxelMaterialType::Wood; }
		if (type_str == "Powder") { material = VoxelMaterialType::Powder; }
	}

	Entry = &Map.New(name, geom, material);
}
void VoxelPalletMapParser::Done(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 0)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 0"); }
	if (Entry == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "no Entry"); }

	if (TextureIndex != 6)
	{
		std::cerr << "VoxelPalletMapParser::Done: TexureIndex not Done\n";
	}

	Entry = nullptr;
	TextureIndex = 0;
}

void VoxelPalletMapParser::Texture(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 3)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 3"); }
	if (Entry == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "no Entry"); }

	FileInfo file(File.Directory().File(cmd_args.ToString(0)));
	Axis2D::Diag diag = StringToAxis2D_Diag(cmd_args.ToString(1));
	Axis2D::Flip flip = StringToAxis2D_Flip(cmd_args.ToString(2));

	Entry -> Textures[TextureIndex].Change(file);
	Entry -> TextureOrientations[TextureIndex] = Axis2D::Orientation(diag, flip);
	TextureIndex++;
}
void VoxelPalletMapParser::Orientation(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 2)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 2"); }
	if (Entry == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "no Entry"); }

	Axis3D::Rel axis0;
	std::string axis0_str = cmd_args.ToString(0);
	if (axis0_str == "Here")       { axis0 = Axis3D::Rel::Here; }
	else if (axis0_str == "PrevX") { axis0 = Axis3D::Rel::PrevX; }
	else if (axis0_str == "PrevY") { axis0 = Axis3D::Rel::PrevY; }
	else if (axis0_str == "PrevZ") { axis0 = Axis3D::Rel::PrevZ; }
	else if (axis0_str == "NextX") { axis0 = Axis3D::Rel::NextX; }
	else if (axis0_str == "NextY") { axis0 = Axis3D::Rel::NextY; }
	else if (axis0_str == "NextZ") { axis0 = Axis3D::Rel::NextZ; }
	else                           { axis0 = Axis3D::Rel::None; }

	Axis3D::Rel axis1;
	std::string axis1_str = cmd_args.ToString(1);
	if (axis1_str == "Here")       { axis1 = Axis3D::Rel::Here; }
	else if (axis1_str == "PrevX") { axis1 = Axis3D::Rel::PrevX; }
	else if (axis1_str == "PrevY") { axis1 = Axis3D::Rel::PrevY; }
	else if (axis1_str == "PrevZ") { axis1 = Axis3D::Rel::PrevZ; }
	else if (axis1_str == "NextX") { axis1 = Axis3D::Rel::NextX; }
	else if (axis1_str == "NextY") { axis1 = Axis3D::Rel::NextY; }
	else if (axis1_str == "NextZ") { axis1 = Axis3D::Rel::NextZ; }
	else                           { axis1 = Axis3D::Rel::None; }

	Entry -> OrientationAxis0 = axis0;
	Entry -> OrientationAxis1 = axis1;
}



void VoxelPalletMapParser::Parse(VoxelPalletMap & map, const FileInfo & file)
{
	VoxelPalletMapParser parser(map);
	parser.File = file;
	parser.ParseFile();
}
