#ifndef  TILE_PARSING_HPP
# define TILE_PARSING_HPP

# include "FileParsing/TextCommand/Func.hpp"
# include "FileParsing/TextCommand/Loop.hpp"

namespace TextCommand { class Args; };

# include "FileInfo.hpp"

class DirectoryInfo;

struct TilePallet;

struct Player;

struct TileParser : public TextCommand::Loop
{
	TilePallet &			Pallet;
	const DirectoryInfo &	MediaDirectory;
	const ::Player &		Player;

	~TileParser();
	TileParser(TilePallet & pallet, const DirectoryInfo & media_dir, const ::Player & player);

	void	PutPolyHedra(const TextCommand::Args & cmd_args);
	
	void	PutNodePos(const TextCommand::Args & cmd_args);
	void	PutNodeTrans(const TextCommand::Args & cmd_args);

	void	PutFeature(const TextCommand::Args & cmd_args);

	static TilePallet *	Parse(const FileInfo & file, const DirectoryInfo & media_dir, const ::Player & player);
};

#endif