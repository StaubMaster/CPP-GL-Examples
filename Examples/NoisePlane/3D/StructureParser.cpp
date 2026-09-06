#include "3D/StructureParser.hpp"
#include "3D/StructureMap.hpp"
#include "3D/Structure.hpp"

#include "3D/Voxel/Pallet/Map.hpp"

// Geometry
# include "3D/Voxel/Pallet/Map.hpp"
# include "3D/Voxel/Pallet.hpp"

// FileManager
#include "FileParsing/TextCommand/Args.hpp"
#include "FileParsing/TextCommand/ArgsStream.hpp"
#include "FileParsing/TextCommand/Exceptions.hpp"
#include "FileParsing/TextCommand/FuncNormal.hpp"
#include "DirectoryInfo.hpp"

// ValueType
#include "ValueType/Box/U3.hpp"

// Debug
#include <iostream>



StructureMapParser::StructureMapParser(StructureMap & map)
	: TextCommand::Loop()
	, Map(map)
{
	Commands.Insert(new TextCommand::FuncNormal("new",			this, &StructureMapParser::New));
	Commands.Insert(new TextCommand::FuncNormal("done",			this, &StructureMapParser::Done));
	Commands.Insert(new TextCommand::FuncNormal("pallet",		this, &StructureMapParser::Pallet));
	Commands.Insert(new TextCommand::FuncNormal("lineX_YZ",		this, &StructureMapParser::LineX_YZ));
	Commands.Insert(new TextCommand::FuncNormal("lineY_XZ",		this, &StructureMapParser::LineY_XZ));
}



void StructureMapParser::New(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 7)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 7"); }
	if (Entry != nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "Entry not done"); }

	std::string name = cmd_args.ToString(0);

	Entry = &Map.New(name);

	VectorU3 center(
		cmd_args.ToUInt32(1),
		cmd_args.ToUInt32(2),
		cmd_args.ToUInt32(3)
	);
	VectorU3 size(
		cmd_args.ToUInt32(4),
		cmd_args.ToUInt32(5),
		cmd_args.ToUInt32(6)
	);

	Entry -> Center = center;
	Entry -> Voxels.Size(size);
}
void StructureMapParser::Done(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 0)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 0"); }
	if (Entry == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "no Entry"); }

	Entry = nullptr;
	PalletChars.Clear();
}

void StructureMapParser::Pallet(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 2)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 2"); }
	if (Entry == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "no Entry"); }

	std::string pallet_char_str = cmd_args.ToString(0);
	if (pallet_char_str.size() != 1)
	{
		throw TextCommand::Exception::InvalidArgument(cmd_args, 0, "should be a Character");
	}

	std::string pallet_name = cmd_args.ToString(1);

	PalletChar pallet_char;
	pallet_char.Pallet = &VoxelPalletMap::StaticMap[pallet_name.c_str()];
	pallet_char.Character = pallet_char_str[0];
	PalletChars.Insert(pallet_char);
}

void StructureMapParser::LineX_YZ(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 3)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 3"); }
	if (Entry == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "no Entry"); }

	VectorU3 udx;
	udx.Y = cmd_args.ToUInt32(0);
	udx.Z = cmd_args.ToUInt32(1);

	std::string str = cmd_args.ToString(2);
	if (str.size() != Entry -> Voxels.Size().X)
	{
		throw TextCommand::Exception::InvalidArgument(cmd_args, 2, "Invalid String Length");
	}

	for (udx.X = 0; udx.X < str.size(); udx.X++)
	{
		char c = str[udx.X];
		if (c == '~') { continue; }
		const VoxelPallet * pallet = nullptr;
		for (unsigned int i = 0; i < PalletChars.Count(); i++)
		{
			if (PalletChars[i].Character == c)
			{
				pallet = PalletChars[i].Pallet;
			}
		}
		if (pallet == nullptr)
		{
			throw TextCommand::Exception::InvalidArgument(cmd_args, 2, "Invalid Pallet Character");
		}
		Entry -> Voxels[udx] = pallet -> ToVoxel();
	}
}
void StructureMapParser::LineY_XZ(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 3)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 3"); }
	if (Entry == nullptr) { throw TextCommand::Exception::InvalidState(cmd_args, "no Entry"); }

	VectorU3 udx;
	udx.X = cmd_args.ToUInt32(0);
	udx.Z = cmd_args.ToUInt32(1);

	std::string str = cmd_args.ToString(2);
	if (str.size() != Entry -> Voxels.Size().Y)
	{
		throw TextCommand::Exception::InvalidArgument(cmd_args, 2, "Invalid String Length");
	}

	for (udx.Y = 0; udx.Y < str.size(); udx.Y++)
	{
		char c = str[udx.Y];
		if (c == '~') { continue; }
		const VoxelPallet * pallet = nullptr;
		for (unsigned int i = 0; i < PalletChars.Count(); i++)
		{
			if (PalletChars[i].Character == c)
			{
				pallet = PalletChars[i].Pallet;
			}
		}
		if (pallet == nullptr)
		{
			throw TextCommand::Exception::InvalidArgument(cmd_args, 2, "Invalid Pallet Character");
		}
		Entry -> Voxels[udx] = pallet -> ToVoxel();
	}
}



void StructureMapParser::Parse(StructureMap & map, const FileInfo & file)
{
	StructureMapParser parser(map);
	parser.File = file;
	parser.ParseFile();
}
