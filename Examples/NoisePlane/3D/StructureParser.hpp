#ifndef  STRUCTURE_PARSER_HPP
# define STRUCTURE_PARSER_HPP

struct StructureMap;
struct Structure;

struct VoxelPallet;

# include "FileParsing/TextCommand/Loop.hpp"
# include "FileParsing/TextCommand/Func.hpp"

# include "FileInfo.hpp"

# include "Generics/Container/Binary.hpp"

struct StructureMapParser : public TextCommand::Loop
{
	StructureMap &	Map;
	Structure *		Entry = nullptr;

	struct PalletChar
	{
		const VoxelPallet *		Pallet = nullptr;
		char					Character = ' ';
	};
	Container::Binary<PalletChar>	PalletChars;

	StructureMapParser() = delete;
	StructureMapParser(StructureMap & map);

	void	New(const TextCommand::Args & cmd_args);
	void	Done(const TextCommand::Args & cmd_args);

	void	Pallet(const TextCommand::Args & cmd_args);

	void	LineX_YZ(const TextCommand::Args & cmd_args);
	void	LineY_XZ(const TextCommand::Args & cmd_args);

	static void		Parse(StructureMap & map, const FileInfo & file);
};

#endif