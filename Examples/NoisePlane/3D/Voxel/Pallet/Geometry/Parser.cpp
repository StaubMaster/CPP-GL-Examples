#include "3D/Voxel/Pallet/Geometry/Parser.hpp"
#include "3D/Voxel/Pallet/Geometry/Map.hpp"
#include "3D/Voxel/Pallet/Geometry.hpp"

// FileManager
#include "FileParsing/TextCommand/Args.hpp"
#include "FileParsing/TextCommand/ArgsStream.hpp"
#include "FileParsing/TextCommand/Exceptions.hpp"
#include "FileParsing/TextCommand/FuncNormal.hpp"

// ValueType
#include "ValueType/Box/U2.hpp"
#include "ValueType/Box/F2.hpp"



void VoxelPalletGeometryMapParser::NewCorner(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 3)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 3"); }

	Corners.Insert(VectorF3(
		cmd_args.ToFloat(0),
		cmd_args.ToFloat(1),
		cmd_args.ToFloat(2)
	));
}



VoxelPalletGeometryMapParser::VoxelPalletGeometryMapParser(VoxelPalletGeometryMap & map)
	: TextCommand::Loop()
	, Map(map)
{
	Commands.Insert(new TextCommand::FuncNormal("newCorner",	this, &VoxelPalletGeometryMapParser::NewCorner));
	Commands.Insert(new TextCommand::FuncNormal("new",			this, &VoxelPalletGeometryMapParser::New));
	Commands.Insert(new TextCommand::FuncNormal("done",			this, &VoxelPalletGeometryMapParser::Done));
	Commands.Insert(new TextCommand::FuncNormal("showAxis",		this, &VoxelPalletGeometryMapParser::ShowAxis));
	Commands.Insert(new TextCommand::FuncNormal("hideAxis",		this, &VoxelPalletGeometryMapParser::HideAxis));
	Commands.Insert(new TextCommand::FuncNormal("uQuad0",		this, &VoxelPalletGeometryMapParser::UQuad0));
	Commands.Insert(new TextCommand::FuncNormal("uQuad1",		this, &VoxelPalletGeometryMapParser::UQuad1));
	Commands.Insert(new TextCommand::FuncNormal("fTri0",		this, &VoxelPalletGeometryMapParser::FTri0));
	Commands.Insert(new TextCommand::FuncNormal("fTri1",		this, &VoxelPalletGeometryMapParser::FTri1));
	Commands.Insert(new TextCommand::FuncNormal("fQuad0",		this, &VoxelPalletGeometryMapParser::FQuad0));
	Commands.Insert(new TextCommand::FuncNormal("fQuad1",		this, &VoxelPalletGeometryMapParser::FQuad1));
}



void VoxelPalletGeometryMapParser::New(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 1)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 1"); }
	if (Entry != nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "Entry not done"); }

	Entry = &Map.New(cmd_args.ToString(0));
}
void VoxelPalletGeometryMapParser::Done(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 0)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 0"); }
	if (Entry == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "no Entry"); }

	Entry -> DataF.Done();
	Entry = nullptr;
	Corners.Clear();
}

/*static AxisRel	StringToAxisRel(const std::string & str)
{
	if (str == "Here") { return AxisRel::Here; }
	else if (str == "PrevX") { return AxisRel::PrevX; }
	else if (str == "PrevY") { return AxisRel::PrevY; }
	else if (str == "PrevZ") { return AxisRel::PrevZ; }
	else if (str == "NextX") { return AxisRel::NextX; }
	else if (str == "NextY") { return AxisRel::NextY; }
	else if (str == "NextZ") { return AxisRel::NextZ; }
	else { return AxisRel::None; }
}*/

void VoxelPalletGeometryMapParser::ShowAxis(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 1)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 1"); }
	if (Entry == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "no Entry"); }

	std::string str = cmd_args.ToString(0);

	if (str == "Here") { return; }
	else if (str == "PrevX") { Entry -> UseF_PrevX = true; }
	else if (str == "PrevY") { Entry -> UseF_PrevY = true; }
	else if (str == "PrevZ") { Entry -> UseF_PrevZ = true; }
	else if (str == "NextX") { Entry -> UseF_NextX = true; }
	else if (str == "NextY") { Entry -> UseF_NextY = true; }
	else if (str == "NextZ") { Entry -> UseF_NextZ = true; }
	else { throw "Invalid Axis Name"; }
}
void VoxelPalletGeometryMapParser::HideAxis(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 1)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 1"); }
	if (Entry == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "no Entry"); }

	std::string str = cmd_args.ToString(0);

	if (str == "Here") { return; }
	else if (str == "PrevX") { Entry -> UseF_PrevX = false; }
	else if (str == "PrevY") { Entry -> UseF_PrevY = false; }
	else if (str == "PrevZ") { Entry -> UseF_PrevZ = false; }
	else if (str == "NextX") { Entry -> UseF_NextX = false; }
	else if (str == "NextY") { Entry -> UseF_NextY = false; }
	else if (str == "NextZ") { Entry -> UseF_NextZ = false; }
	else { throw "Invalid Axis Name"; }
}



#include <iostream>
static VectorU3 BinaryStringToVecU3(std::string str)
{
	if (str.length() != 3)
	{
		throw "bad String Length";
	}

	unsigned int v[3];
	for (unsigned int i = 0; i < 3; i++)
	{
		char c = str[i];
		if (c == '0')
		{
			v[i] = 0;
		}
		else if (c == '1')
		{
			v[i] = 1;
		}
		else
		{
			throw "BinaryString Invalid";
		}
	}

	return VectorU3(v[2], v[1], v[0]);
}

VoxelGeometryDataU::Face & VoxelPalletGeometryMapParser::ToFaceU(std::string str)
{
	if (str == "Here") { throw "Invalid FaceU Axis"; }
	else if (str == "PrevX") { return Entry -> DataU.PrevX; }
	else if (str == "PrevY") { return Entry -> DataU.PrevY; }
	else if (str == "PrevZ") { return Entry -> DataU.PrevZ; }
	else if (str == "NextX") { return Entry -> DataU.NextX; }
	else if (str == "NextY") { return Entry -> DataU.NextY; }
	else if (str == "NextZ") { return Entry -> DataU.NextZ; }
	else { throw "Invalid FaceU Name"; }
}

// uQuad0   prevX   000 010 100 110   0 0 1 1   0
void VoxelPalletGeometryMapParser::UQuad0(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 10)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 10"); }
	if (Entry == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "no Entry"); }

	VoxelGeometryDataU::Face & face = ToFaceU(cmd_args.ToString(0));

	VectorU3 p00 = BinaryStringToVecU3(cmd_args.ToString(1));
	VectorU3 p01 = BinaryStringToVecU3(cmd_args.ToString(2));
	VectorU3 p10 = BinaryStringToVecU3(cmd_args.ToString(3));
	VectorU3 p11 = BinaryStringToVecU3(cmd_args.ToString(4));

	BoxU2 box(
		VectorU2(
			cmd_args.ToUInt32(5),
			cmd_args.ToUInt32(6)
		),
		VectorU2(
			cmd_args.ToUInt32(7),
			cmd_args.ToUInt32(8)
		)
	);

	unsigned int tex = cmd_args.ToUInt32(9);

	face.Quad0(p00, p01, p10, p11, box, tex);
}
void VoxelPalletGeometryMapParser::UQuad1(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 10)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 10"); }
	if (Entry == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "no Entry"); }

	VoxelGeometryDataU::Face & face = ToFaceU(cmd_args.ToString(0));

	VectorU3 p00 = BinaryStringToVecU3(cmd_args.ToString(1));
	VectorU3 p01 = BinaryStringToVecU3(cmd_args.ToString(2));
	VectorU3 p10 = BinaryStringToVecU3(cmd_args.ToString(3));
	VectorU3 p11 = BinaryStringToVecU3(cmd_args.ToString(4));

	BoxU2 box(
		VectorU2(
			cmd_args.ToUInt32(5),
			cmd_args.ToUInt32(6)
		),
		VectorU2(
			cmd_args.ToUInt32(7),
			cmd_args.ToUInt32(8)
		)
	);

	unsigned int tex = cmd_args.ToUInt32(9);

	face.Quad1(p00, p01, p10, p11, box, tex);
}




VoxelGeometryDataF::Axis & VoxelPalletGeometryMapParser::ToFaceF(std::string str)
{
	if (str == "Here") { return Entry -> DataF.Here; }
	else if (str == "PrevX") { return Entry -> DataF.PrevX; }
	else if (str == "PrevY") { return Entry -> DataF.PrevY; }
	else if (str == "PrevZ") { return Entry -> DataF.PrevZ; }
	else if (str == "NextX") { return Entry -> DataF.NextX; }
	else if (str == "NextY") { return Entry -> DataF.NextY; }
	else if (str == "NextZ") { return Entry -> DataF.NextZ; }
	else { throw "Invalid FaceF Name"; }
}

// void	Tri0(VectorF3 p0, VectorF3 p1, VectorF3 p2, VectorF2 t0, VectorF2 t1, VectorF2 t2, unsigned int tex);
// fTri0   prevX   idx0 idx1 idx2   0.0 0.0  0.0 0.0  0.0 0.0   0
void VoxelPalletGeometryMapParser::FTri0(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 11)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 11"); }
	if (Entry == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "no Entry"); }

	VoxelGeometryDataF::Axis & face = ToFaceF(cmd_args.ToString(0));

	VectorF3 p0 = Corners[cmd_args.ToUInt32(1)];
	VectorF3 p1 = Corners[cmd_args.ToUInt32(2)];
	VectorF3 p2 = Corners[cmd_args.ToUInt32(3)];

	VectorF2 t0(
		cmd_args.ToFloat(4),
		cmd_args.ToFloat(5)
	);
	VectorF2 t1(
		cmd_args.ToFloat(6),
		cmd_args.ToFloat(7)
	);
	VectorF2 t2(
		cmd_args.ToFloat(8),
		cmd_args.ToFloat(9)
	);

	unsigned int tex = cmd_args.ToUInt32(10);

	face.Tri0(p0, p1, p2, t0, t1, t2, tex);
}
void VoxelPalletGeometryMapParser::FTri1(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 11)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 11"); }
	if (Entry == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "no Entry"); }

	VoxelGeometryDataF::Axis & face = ToFaceF(cmd_args.ToString(0));

	VectorF3 p0 = Corners[cmd_args.ToUInt32(1)];
	VectorF3 p1 = Corners[cmd_args.ToUInt32(2)];
	VectorF3 p2 = Corners[cmd_args.ToUInt32(3)];

	VectorF2 t0(
		cmd_args.ToFloat(4),
		cmd_args.ToFloat(5)
	);
	VectorF2 t1(
		cmd_args.ToFloat(6),
		cmd_args.ToFloat(7)
	);
	VectorF2 t2(
		cmd_args.ToFloat(8),
		cmd_args.ToFloat(9)
	);

	unsigned int tex = cmd_args.ToUInt32(10);

	face.Tri1(p0, p1, p2, t0, t1, t2, tex);
}

// DataF.PrevX.Quad0(pos[0b000], pos[0b010], pos[0b100], pos[0b110], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 0);
// fQuad0   prevX   0b000 0b010 0b100 0b110   0.0 0.0 1.0 1.0   0
void VoxelPalletGeometryMapParser::FQuad0(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 10)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 10"); }
	if (Entry == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "no Entry"); }

	VoxelGeometryDataF::Axis & face = ToFaceF(cmd_args.ToString(0));

	VectorF3 p00 = Corners[cmd_args.ToUInt32(1)];
	VectorF3 p01 = Corners[cmd_args.ToUInt32(2)];
	VectorF3 p10 = Corners[cmd_args.ToUInt32(3)];
	VectorF3 p11 = Corners[cmd_args.ToUInt32(4)];

	BoxF2 box(
		VectorF2(
			cmd_args.ToFloat(5),
			cmd_args.ToFloat(6)
		),
		VectorF2(
			cmd_args.ToFloat(7),
			cmd_args.ToFloat(8)
		)
	);

	unsigned int tex = cmd_args.ToUInt32(9);

	face.Quad0(p00, p01, p10, p11, box, tex);
}
void VoxelPalletGeometryMapParser::FQuad1(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 10)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 10"); }
	if (Entry == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "no Entry"); }

	VoxelGeometryDataF::Axis & face = ToFaceF(cmd_args.ToString(0));

	VectorF3 p00 = Corners[cmd_args.ToUInt32(1)];
	VectorF3 p01 = Corners[cmd_args.ToUInt32(2)];
	VectorF3 p10 = Corners[cmd_args.ToUInt32(3)];
	VectorF3 p11 = Corners[cmd_args.ToUInt32(4)];

	BoxF2 box(
		VectorF2(
			cmd_args.ToFloat(5),
			cmd_args.ToFloat(6)
		),
		VectorF2(
			cmd_args.ToFloat(7),
			cmd_args.ToFloat(8)
		)
	);

	unsigned int tex = cmd_args.ToUInt32(9);

	face.Quad1(p00, p01, p10, p11, box, tex);
}



void VoxelPalletGeometryMapParser::Parse(VoxelPalletGeometryMap & map, const FileInfo & file)
{
	VoxelPalletGeometryMapParser parser(map);
	parser.File = file;
	parser.ParseFile();
}
