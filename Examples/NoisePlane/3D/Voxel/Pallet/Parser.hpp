#ifndef  VOXEL_PALLET_PARSER_HPP
# define VOXEL_PALLET_PARSER_HPP

struct VoxelPalletMap;
struct VoxelPallet;

# include "FileParsing/TextCommand/Loop.hpp"
# include "FileParsing/TextCommand/Func.hpp"

# include "FileInfo.hpp"

# include "Generics/Container/Binary.hpp"

struct VoxelPalletMapParser : public TextCommand::Loop
{
	VoxelPalletMap &	Map;
	VoxelPallet *		Entry = nullptr;
	unsigned int		TextureIndex = 0;

	VoxelPalletMapParser() = delete;
	VoxelPalletMapParser(VoxelPalletMap & map);

	void	New(const TextCommand::Args & cmd_args);
	void	Done(const TextCommand::Args & cmd_args);

	void	Texture(const TextCommand::Args & cmd_args);

	static void		Parse(VoxelPalletMap & map, const FileInfo & file);
};

#endif