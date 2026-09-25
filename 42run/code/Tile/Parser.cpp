#include "Tile/Parser.hpp"
#include "Tile/Pallet.hpp"

#include "Player.hpp"

// File
#include "DirectoryInfo.hpp"
#include "FileParsing/TextCommand/Args.hpp"
#include "FileParsing/TextCommand/ArgsStream.hpp"
#include "FileParsing/TextCommand/FuncNormal.hpp"
#include "FileParsing/TextCommand/Exceptions.hpp"

// PolyHedra
#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Parser.hpp"

// NewPolyHedra
#include "NewPolyHedra/DataType/Basic3D/ObjectManager.hpp"



TileParser::~TileParser()
{
	for (unsigned int i = 0; i < Commands.Count(); i++)
	{
		delete Commands[i];
	}
}
TileParser::TileParser(TilePallet & pallet, const DirectoryInfo & media_dir, const ::Player & player)
	: Pallet(pallet)
	, MediaDirectory(media_dir)
	, Player(player)
{
	Commands.Insert(new TextCommand::FuncNormal("polyhedra",	this, &TileParser::PutPolyHedra));
	Commands.Insert(new TextCommand::FuncNormal("nodePos",		this, &TileParser::PutNodePos));
	Commands.Insert(new TextCommand::FuncNormal("nodeTrans",	this, &TileParser::PutNodeTrans));
	Commands.Insert(new TextCommand::FuncNormal("feature",		this, &TileParser::PutFeature));
}

void TileParser::PutPolyHedra(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 1)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 1"); }

	if (Pallet.Object != nullptr)
	{
		TextCommand::Exception::InvalidState(cmd_args, "Tile already has PolyHedra");
	}

	FileInfo file = MediaDirectory.File(cmd_args.ToString(0));
	if (!file.Exists()) { throw TextCommand::Exception::InvalidArgument(cmd_args, 0, "Invalid File"); }
	PolyHedra * polyhedra = PolyHedraParser::Load(file, nullptr, nullptr);

	// compact this whole thing ?
	// NewPolyHedra::Basic3D::PalletObjectManager::FindMake(PolyHedra*)
	Pallet.Object = (NewPolyHedra::Basic3D::PalletObjectManager*)NewPolyHedra::Basic3D::ObjectManager::Current -> PalletObjectManagersFindMake(polyhedra);
}

void TileParser::PutNodePos(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 4)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 4"); }

	std::string path_str = cmd_args.ToString(0);
	Trans3D node(VectorF3(
		cmd_args.ToFloat(1),
		cmd_args.ToFloat(2),
		cmd_args.ToFloat(3)
	));

	     if (path_str == "C")	{ Pallet.PathTo.NewNode(node); }
	else if (path_str == "M")	{ Pallet.Path[0].NewNode(node); }
	else if (path_str == "L")	{ Pallet.Path[1].NewNode(node); }
	else if (path_str == "R")	{ Pallet.Path[2].NewNode(node); }
	else { throw TextCommand::Exception::InvalidArgument(cmd_args, 0, "Unkown Path String"); }
}
void TileParser::PutNodeTrans(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() == 7)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 7"); }

	std::string path_str = cmd_args.ToString(0);
	Trans3D node(VectorF3(
		cmd_args.ToFloat(1),
		cmd_args.ToFloat(2),
		cmd_args.ToFloat(3)
	),
	EulerAngle3D::Degrees(
		cmd_args.ToFloat(4),
		cmd_args.ToFloat(5),
		cmd_args.ToFloat(6)
	));

	     if (path_str == "C")	{ Pallet.PathTo.NewNode(node); }
	else if (path_str == "M")	{ Pallet.Path[0].NewNode(node); }
	else if (path_str == "L")	{ Pallet.Path[1].NewNode(node); }
	else if (path_str == "R")	{ Pallet.Path[2].NewNode(node); }
	else { throw TextCommand::Exception::InvalidArgument(cmd_args, 0, "Unkown Path String"); }
}

#include "Tile/Feature/Pallet/DeathFall.hpp"
#include "Tile/Feature/Pallet/DeathWall.hpp"
#include "Tile/Feature/Pallet/CoinParabola.hpp"
#include <iostream>

void TileParser::PutFeature(const TextCommand::Args & cmd_args)
{
	if (!(cmd_args.Count() >= 1)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n >= 1"); }

	std::string feature_name = cmd_args.ToString(0);
	if (feature_name == "DeathFall")
	{
		if (!(cmd_args.Count() == 5)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 5"); }

		std::string path_str = cmd_args.ToString(1);
		EPath path;
		if      (path_str == "M")	{ path = EPath::Middle; }
		else if (path_str == "L")	{ path = EPath::Left; }
		else if (path_str == "R")	{ path = EPath::Right; }
		else { throw TextCommand::Exception::InvalidArgument(cmd_args, 1, "Unkown Path String"); }

		std::string side_str = cmd_args.ToString(2);
		EPath side;
		if      (side_str == "M")	{ side = EPath::Middle; }
		else if (side_str == "L")	{ side = EPath::Left; }
		else if (side_str == "R")	{ side = EPath::Right; }
		else { throw TextCommand::Exception::InvalidArgument(cmd_args, 2, "Unkown Path String"); }

		BoxF1 dist(
			cmd_args.ToFloat(3),
			cmd_args.ToFloat(4)
		);

		Pallet.Features.Insert(new TileFeaturePalletDeathFall(
			path,
			side,
			dist
		));
	}
	else if (feature_name == "DeathWall")
	{
		if (!(cmd_args.Count() == 7)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 7"); }

		std::string path_str = cmd_args.ToString(1);
		EPath path;
		if      (path_str == "M")	{ path = EPath::Middle; }
		else if (path_str == "L")	{ path = EPath::Left; }
		else if (path_str == "R")	{ path = EPath::Right; }
		else { throw TextCommand::Exception::InvalidArgument(cmd_args, 1, "Unkown Path String"); }

		std::string side_str = cmd_args.ToString(2);
		EPath side;
		if      (side_str == "M")	{ side = EPath::Middle; }
		else if (side_str == "L")	{ side = EPath::Left; }
		else if (side_str == "R")	{ side = EPath::Right; }
		else { throw TextCommand::Exception::InvalidArgument(cmd_args, 2, "Unkown Path String"); }

		BoxF1 dist(
			cmd_args.ToFloat(3),
			cmd_args.ToFloat(4)
		);

		BoxF1 height(
			cmd_args.ToFloat(5),
			cmd_args.ToFloat(6)
		);

		Pallet.Features.Insert(new TileFeaturePalletDeathWall(
			path,
			side,
			dist,
			height
		));
	}
	else if (feature_name == "CoinParabola")
	{
		if (!(cmd_args.Count() == 4)) { throw TextCommand::Exception::InvalidArgumentCount(cmd_args, "n == 4"); }

		std::string path_str = cmd_args.ToString(1);
		EPath path;
		if      (path_str == "M")	{ path = EPath::Middle; }
		else if (path_str == "L")	{ path = EPath::Left; }
		else if (path_str == "R")	{ path = EPath::Right; }
		else { throw TextCommand::Exception::InvalidArgument(cmd_args, 1, "Unkown Path String"); }

		std::string side_str = cmd_args.ToString(2);
		EPath side;
		if      (side_str == "M")	{ side = EPath::Middle; }
		else if (side_str == "L")	{ side = EPath::Left; }
		else if (side_str == "R")	{ side = EPath::Right; }
		else { throw TextCommand::Exception::InvalidArgument(cmd_args, 2, "Unkown Path String"); }

		Pallet.Features.Insert(new TileFeaturePalletCoinParabola(
			Player,
			path,
			side,
			cmd_args.ToFloat(3)
		));
	}
	else
	{
		throw TextCommand::Exception::InvalidArgument(cmd_args, 0, "Unkown Feature");
	}
}

TilePallet * TileParser::Parse(const FileInfo & file, const DirectoryInfo & media_dir, const ::Player & player)
{
	TilePallet * pallet = new TilePallet();
	TileParser data(*pallet, media_dir, player);
	data.File = file;
	data.ParseFile();
	pallet -> Init();
	return pallet;
}
